/*
  RedFly Lib for Arduino
  by Watterott electronic (www.watterott.com)
 */

#include <inttypes.h>
#if defined(__AVR__)
# include <avr/io.h>
# include <avr/pgmspace.h>
# include <util/delay.h>
#else
# include <chip.h>
# include <itoa.h>
#endif
#if ARDUINO >= 100
# include "Arduino.h"
#else
# include "WProgram.h"
#endif
#include "RedFlyCommands.h"
#include "RedFly.h"
#include "RedFlyClient.h"
#include "RedFlyServer.h"
#include "RedFlyNBNS.h"


#define RX_PIN          (0)
#define TX_PIN          (1)
#define RST_PIN         (2)
#define CS_PIN          (3)

#define RST_DISABLE()   digitalWrite(RST_PIN, HIGH)
#define RST_ENABLE()    digitalWrite(RST_PIN, LOW)

#define CS_DISABLE()    digitalWrite(CS_PIN, HIGH)
#define CS_ENABLE()     digitalWrite(CS_PIN, LOW)

#if defined(__AVR__) && defined(UBRRH) && defined(UBRRL)
# define _UCSRA_  UCSRA
# define _RXC_    RXC
# define _UCSRC_  UCSRC
# define _USBS_   USBS
# define _SERIAL_ Serial
#elif defined(__AVR__) && !defined(UBRR0H) && !defined(UBRR0L)
# define _UCSRA_ UCSR1A
# define _RXC_   RXC1
# define _UCSRC_ UCSR1C
# define _USBS_  USBS1
# define _SERIAL_ Serial1
#elif defined(__AVR__)
# define _UCSRA_ UCSR0A
# define _RXC_   RXC0
# define _UCSRC_ UCSR0C
# define _USBS_  USBS0
# define _SERIAL_ Serial
#else
# define _SERIAL_ Serial
# define _USART_  USART0
#endif


REDFLY RedFly;


//-------------------- Constructor/Destructor --------------------


REDFLY::REDFLY(void)
{
  return;
}


REDFLY::~REDFLY(void)
{
  return;
}


//-------------------- Public --------------------


uint8_t REDFLY::init(uint32_t br, uint8_t pwr)
{
  uint8_t ret=0xFF, i;
  uint32_t ms;

  //init pins
#ifdef CS_PIN
  pinMode(CS_PIN, OUTPUT);
  CS_DISABLE(); //deselect
#endif
#ifdef RST_PIN
  pinMode(RST_PIN, OUTPUT);
  RST_ENABLE(); //reset on
#endif
#ifdef TX_PIN
  pinMode(TX_PIN, OUTPUT);
  digitalWrite(TX_PIN, HIGH);
#endif
#ifdef RX_PIN
  pinMode(RX_PIN, INPUT);
  digitalWrite(RX_PIN, HIGH); //pull-up on
#endif

  //reset vars
  memset(ipaddr, 0, sizeof(ipaddr));
  memset(buffer, 0, sizeof(buffer));

  //set serial port config
  baudrate = br;
  setbaudrate(br);

  //enable module communication
  enable();

  //reset module
  RST_ENABLE();
  delay_10ms(5); //wait 50ms
  RST_DISABLE();

  //auto baud rate detection
  delay_10ms(11); //wait 110ms for module boot-up
  for(i=4; i!=0; i--) //try 4 times
  {
    write(0x1C); //transmit 0x1C
    for(ms=millis(); (millis()-ms) < 200;) //wait 200ms for response
    {
      if(available())
      {
        if(read() == 0x55) //wait for 0x55
        {
          write(0x55); //transmit 0x55
          delay_10ms(10);  //wait 100ms
          //skip firmware upgrade question at power on
          write('n');
          write('\n');
          ret = 0xFE;
          i = 1;  //break 1st for loop
          break; //break 2nd for loop
        }
      }
    }
  }
  delay_10ms(20); //wait 200ms for booting

  //get firmware version and set config
  // if(ret == 0xFE)
  // {
    for(i=3; i!=0; i--) //try 3 times
    {
      flush();
      if(cmd(PSTR(CMD_FWVERSION)) == 0)
      {
        //cmd(PSTR(CMD_RESET)); //soft reset
        cmd(PSTR(CMD_BAND BAND24));
        cmd(PSTR(CMD_INIT));
        tx_power = pwr;
        ret = 0;
        break;
      }
      delay_10ms(10);
    }
  // }

  if(ret)
  {
    disable();
  }

  return ret;
}


uint8_t REDFLY::init(uint8_t pwr) { return init(REDFLY_BAUDRATE, pwr); }
uint8_t REDFLY::init(void)        { return init(REDFLY_BAUDRATE, HIGH_POWER); }


void REDFLY::enable(void) //select module
{
  flush(); //clear buffers
  setbaudrate(baudrate);
  read_state = 0;
  CS_ENABLE();

  return;
}


void REDFLY::disable(void) //deselect module
{
  flush(); //clear buffers
  read_state = 0;
  CS_DISABLE();

  return;
}


uint8_t REDFLY::getversion(char *ver) //return module firmware version
{
  uint8_t ret;

  for(uint8_t i=3; i!=0; i--) //try 3 times
  {
    memset(buffer, 0, sizeof(buffer));
    ret = cmd(buffer, sizeof(buffer), PSTR(CMD_FWVERSION)); //OKa.b.c
    if(ret == 0)
    {
      //buffer[0] = 'O', buffer[1] = 'K'
      memcpy(&ver[0], &buffer[2], 5);
      ver[5] = 0;
      return 0;
    }
  }

  return ret;
}


uint8_t REDFLY::getmac(uint8_t *mac) //return module MAC address
{
  uint8_t ret;

  for(uint8_t i=3; i!=0; i--) //try 3 times
  {
    memset(buffer, 0, sizeof(buffer));
    ret = cmd(buffer, sizeof(buffer), PSTR(CMD_MAC)); //OKabcdef
    if(ret == 0)
    {
      memcpy(&mac[0], &buffer[2], 6); //buffer[0] = 'O', buffer[1] = 'K'
      return 0;
    }
  }

  return ret;
}


uint8_t REDFLY::getlocalip(uint8_t *ip) //return module IP address
{
  if(ipaddr[0])
  {
    memcpy(ip, ipaddr, 4);
    return 0;
  }

  return 1;
}


uint8_t REDFLY::getip(char *host, uint8_t *ip) //return IP addr from host/domain
{
  uint8_t ret;

  for(uint8_t i=3; i!=0; i--) //try 3 times
  {
    memset(buffer, 0, sizeof(buffer));
    ret = cmd(buffer, sizeof(buffer), PSTR(CMD_DNSGET), (uint8_t*)host, strlen(host)); //OKx...
    if(ret == 0)
    {
      if(buffer[2]) //IP received?
      {
        memcpy(&ip[0], &buffer[3], 4);
        return 0;
      }
    }
  }

  return ret;
}


#define NTP_PORT       (123)
#define NTP_PACKETLEN  (48)
#define NTP_FLAGOFFSET (0)
#define NTP_TIMEOFFSET (40)
uint32_t REDFLY::gettime(uint8_t *server, uint16_t port)
{
  uint8_t buf[64]; //min. NTP_PACKETLEN
  uint32_t time=0UL, ms;
  uint8_t hNTP, sock, buf_len, *ptr;
  uint16_t rd, len;
  
  if(port == 0)
  {
    port = NTP_PORT;
  }

  //open connection to server
  hNTP = socketConnect(PROTO_UDP, server, port, port);
  if(hNTP != INVALID_SOCKET)
  {
    //send NTP request
    memset(buf, 0, NTP_PACKETLEN);
    buf[NTP_FLAGOFFSET] = (0<<6)|(1<<3)|(3<<0); //NTP flags: LI=0 | VN=1 | Mode=3 -> Client
    if(socketSend(hNTP, buf, NTP_PACKETLEN) == 0)
    {
      //get data
      ptr     = buf;
      buf_len = 0;
      for(ms=millis(); (millis()-ms) < 3000;) //wait max. 3s
      {
        sock = hNTP;
        rd = socketRead(&sock, &len, ptr, sizeof(buf)-buf_len);
        if((rd != 0) && (rd != 0xFFFF)) //0xFFFF = connection closed
        {
          ptr     += rd;
          buf_len += rd;
        }
        if(buf_len && (len == 0)) //all data received?
        {
          break;
        }
      }
      //check data
      if((buf_len >= NTP_PACKETLEN) && ((buf[NTP_FLAGOFFSET]&0x07) == 4)) //NTP flags: Mode=4 -> Server
      {
        //time = (uint32_t)*((uint32_t*)&buf[NTP_TIMEOFFSET]);
        time = (((uint32_t)buf[NTP_TIMEOFFSET+0])<<24)|
               (((uint32_t)buf[NTP_TIMEOFFSET+1])<<16)|
               (((uint32_t)buf[NTP_TIMEOFFSET+2])<< 8)|
               (((uint32_t)buf[NTP_TIMEOFFSET+3])<< 0); //swap32
        time -= 2208988800UL; //sub seconds 1900-1970
      }
    }
    socketClose(hNTP);
  }

  return time;
}


uint32_t REDFLY::gettime(uint8_t *server){ return gettime(server, 0); };


uint8_t REDFLY::getrssi(void) //return signal strength for current connection
{
  for(uint8_t i=3; i!=0; i--) //try 3 times
  {
    memset(buffer, 0, sizeof(buffer));
    if(cmd(buffer, sizeof(buffer), PSTR(CMD_RSSI)) == 0) //OKx
    {
      return buffer[2];
    }
  }

  return 0;
}


uint8_t REDFLY::getbssid(char *ssid, uint8_t *mac) //return SSID and MAC, call after scan()
{
  uint8_t ret;

  memset(buffer, 0, sizeof(buffer));
  
  ret = cmd(buffer, sizeof(buffer), PSTR(CMD_BSSID));

  if(ret == 0) //successful
  {
    //buffer[0] = 'O', buffer[1] = 'K'
    memcpy(ssid, &buffer[2], 32); //SSID
    ssid[32] = 0; //32+1
    memcpy(&mac[0], &buffer[34], 6); //MAC
  }
  else
  {
    ssid[0] = 0;
  }

  return ret;
}


uint8_t REDFLY::gettype(char *ssid, uint8_t *type) //return SSID and network type (0=Ad-hoc, 1=Infrastructure), call after scan()
{
  uint8_t ret;

  memset(buffer, 0, sizeof(buffer));
  
  ret = cmd(buffer, sizeof(buffer), PSTR(CMD_NWTYPE));

  if(ret == 0) //successful
  {
    //buffer[0] = 'O', buffer[1] = 'K'
    memcpy(ssid, &buffer[2], 32); //SSID
    ssid[32] = 0; //32+1
    *type = buffer[34]; //type
  }
  else
  {
    ssid[0] = 0;
  }

  return ret;
}


uint8_t REDFLY::scan(void)
{
  cmd(PSTR(CMD_NUMSCAN "0")); //return all results on scan command

  return cmd(PSTR(CMD_SCAN "0"));
}


uint8_t REDFLY::scan(uint8_t chn, char *ssid, uint8_t *mode, uint8_t *rssi) //chn 0 = all
{
  uint8_t ret, len;

  memset(buffer, 0, sizeof(buffer));

  cmd(PSTR(CMD_NUMSCAN "1")); //return only one result on scan command

  if(ssid[0] != 0) //scan for ssid
  {
    uitoa(chn, (char*)&buffer[0]); //chn
    len = strlen((char*)buffer);
    strcat_P((char*)&buffer[len], PSTR(",")); //,
    len = strlen((char*)buffer);
    strcat((char*)&buffer[len], ssid); //ssid
    ret = cmd(buffer, sizeof(buffer), PSTR(CMD_SCAN), (char*)buffer);
  }
  else
  {
    ret = cmd(buffer, sizeof(buffer), PSTR(CMD_SCAN), chn);
  }

  if(ret == 0) //scan successful
  {
    memcpy(ssid, &buffer[2], 32); //SSID
    ssid[32] = 0; //32+1
    if(mode)
    {
      *mode = buffer[34];
    }
    if(rssi)
    {
      *rssi = buffer[35];
    }
  }
  else
  {
    if(rssi)
    {
      *rssi = 0;
    }
  }

  return ret;
}


uint8_t REDFLY::scan(char *ssid, uint8_t *mode, uint8_t *rssi) { return scan(0, ssid, mode, rssi); }
uint8_t REDFLY::scan(char *ssid)                               { return scan(0, ssid,    0,    0); }


uint8_t REDFLY::nextscan(char *ssid, uint8_t *mode, uint8_t *rssi)
{
  uint8_t ret;

  memset(buffer, 0, sizeof(buffer));

  ret = cmd(buffer, sizeof(buffer), PSTR(CMD_NEXTSCAN));

  if(ret == 0) //scan successful
  {
    memcpy(ssid, &buffer[2], 32); //SSID
    ssid[32] = 0; //32+1
    if(mode)
    {
      *mode = buffer[34];
    }
    if(rssi)
    {
      *rssi = buffer[35];
    }
  }
  else
  {
    if(rssi)
    {
      *rssi = 0;
    }
  }

  return ret;
}


uint8_t REDFLY::nextscan(char *ssid) { nextscan(ssid, 0, 0); }


uint8_t REDFLY::join(char *ssid, char *key, uint8_t net, uint8_t chn, uint8_t authmode)
{
  uint8_t ret=0;

  //network
  switch(net)
  {
    case INFRASTRUCTURE: 
      cmd(PSTR(CMD_NETWORK "INFRASTRUCTURE"));
      break;
    case IBSS_JOINER:
      if(key)
      {
        cmd(PSTR(CMD_NETWORK "IBSS_SEC,0,0"));
      }
      else
      {
        cmd(PSTR(CMD_NETWORK "IBSS,0,0"));
      }
      break;
    case IBSS_CREATOR:
      if(key)
      {
        cmd(PSTR(CMD_NETWORK "IBSS_SEC,1,"), chn);
      }
      else
      {
        cmd(PSTR(CMD_NETWORK "IBSS,1,"), chn);
      }
      break;
  }

  //authentication mode
  if(authmode <= 4)
  {
    cmd(PSTR(CMD_AUTHMODE), authmode);
  }

  //key
  if(key)
  {
    cmd(PSTR(CMD_PSK), key);
  }

  //join
  switch(tx_power)
  {
    //auto data rate
    case LOW_POWER:      ret = cmd(PSTR(CMD_JOIN), ssid, PSTR(JOIN_LOWPW));  break;
    case MED_POWER:      ret = cmd(PSTR(CMD_JOIN), ssid, PSTR(JOIN_MEDPW));  break;
    case HIGH_POWER:     ret = cmd(PSTR(CMD_JOIN), ssid, PSTR(JOIN_HIGHPW)); break;
    //1Mbps
    case LOW_POWER_1M:   ret = cmd(PSTR(CMD_JOIN), ssid, PSTR(JOIN_LOWPW1M));  break;
    case MED_POWER_1M:   ret = cmd(PSTR(CMD_JOIN), ssid, PSTR(JOIN_MEDPW1M));  break;
    case HIGH_POWER_1M:  ret = cmd(PSTR(CMD_JOIN), ssid, PSTR(JOIN_HIGHPW1M)); break;
    //2Mbps
    case LOW_POWER_2M:   ret = cmd(PSTR(CMD_JOIN), ssid, PSTR(JOIN_LOWPW2M));  break;
    case MED_POWER_2M:   ret = cmd(PSTR(CMD_JOIN), ssid, PSTR(JOIN_MEDPW2M));  break;
    case HIGH_POWER_2M:  ret = cmd(PSTR(CMD_JOIN), ssid, PSTR(JOIN_HIGHPW2M)); break;
    //11Mbps
    case LOW_POWER_11M:  ret = cmd(PSTR(CMD_JOIN), ssid, PSTR(JOIN_LOWPW11M));  break;
    case MED_POWER_11M:  ret = cmd(PSTR(CMD_JOIN), ssid, PSTR(JOIN_MEDPW11M));  break;
    case HIGH_POWER_11M: ret = cmd(PSTR(CMD_JOIN), ssid, PSTR(JOIN_HIGHPW11M)); break;
    //12Mbps
    case LOW_POWER_12M:  ret = cmd(PSTR(CMD_JOIN), ssid, PSTR(JOIN_LOWPW12M));  break;
    case MED_POWER_12M:  ret = cmd(PSTR(CMD_JOIN), ssid, PSTR(JOIN_MEDPW12M));  break;
    case HIGH_POWER_12M: ret = cmd(PSTR(CMD_JOIN), ssid, PSTR(JOIN_HIGHPW12M)); break;
    //24Mbps
    case LOW_POWER_24M:  ret = cmd(PSTR(CMD_JOIN), ssid, PSTR(JOIN_LOWPW24M));  break;
    case MED_POWER_24M:  ret = cmd(PSTR(CMD_JOIN), ssid, PSTR(JOIN_MEDPW24M));  break;
    case HIGH_POWER_24M: ret = cmd(PSTR(CMD_JOIN), ssid, PSTR(JOIN_HIGHPW24M)); break;
    //54Mbps
    case LOW_POWER_54M:  ret = cmd(PSTR(CMD_JOIN), ssid, PSTR(JOIN_LOWPW54M));  break;
    case MED_POWER_54M:  ret = cmd(PSTR(CMD_JOIN), ssid, PSTR(JOIN_MEDPW54M));  break;
    case HIGH_POWER_54M: ret = cmd(PSTR(CMD_JOIN), ssid, PSTR(JOIN_HIGHPW54M)); break;
  }

  return ret;
}


uint8_t REDFLY::join(char *ssid, char *key, uint8_t net, uint8_t chn) { return join(ssid, key,            net, chn, 0xFF); } //IBSS_CREATOR
uint8_t REDFLY::join(char *ssid,            uint8_t net, uint8_t chn) { return join(ssid,   0,            net, chn, 0xFF); } //IBSS_CREATOR
uint8_t REDFLY::join(char *ssid, char *key, uint8_t net)              { return join(ssid, key,            net,   0, 0xFF); } //INFRASTRUCTURE or IBSS_JOINER
uint8_t REDFLY::join(char *ssid,            uint8_t net)              { return join(ssid,   0,            net,   0, 0xFF); } //INFRASTRUCTURE or IBSS_JOINER
uint8_t REDFLY::join(char *ssid, char *key)                           { return join(ssid, key, INFRASTRUCTURE,   0, 0xFF); } //INFRASTRUCTURE
uint8_t REDFLY::join(char *ssid)                                      { return join(ssid,   0, INFRASTRUCTURE,   0, 0xFF); } //INFRASTRUCTURE


uint8_t REDFLY::disconnect(void)
{
  socketReset();
  memset(ipaddr, 0, sizeof(ipaddr));

  return cmd(PSTR(CMD_DISCONN));
}


uint8_t REDFLY::begin(uint8_t dhcp, uint8_t *ip, uint8_t *dns, uint8_t *gateway, uint8_t *netmask)
{
  uint8_t len;

  //reset sockets and IP addr
  socketReset();
  memset(ipaddr, 0, sizeof(ipaddr));
  memset(buffer, 0, sizeof(buffer));

  //dhcp or auto ip
  if(dhcp == 2) //Auto-IP
  {
    if(cmd(buffer, sizeof(buffer), PSTR(CMD_IPCONF IPCONF_AUTOIP)) == 0) //OKMACaddrIPaddrSUBNETGateway
    {
      memcpy(&ipaddr[0], &buffer[8], 4);
      return 0;
    }
    return 2;
  }
  else if(dhcp) //DHCP
  {
    if(cmd(buffer, sizeof(buffer), PSTR(CMD_IPCONF IPCONF_DHCP)) == 0) //OKMACaddrIPaddrSUBNETGateway
    {
      memcpy(&ipaddr[0], &buffer[8], 4);
      return 0;
    }
    return 1;
  }

  //static ip settings
  if(dns)
  {
    iptoa(dns, (char*)&buffer[0]);
    cmd(PSTR(CMD_DNSSERVER), (char*)buffer); //set DNS server (FW >= 4.3.0 required)
  }
  if(ip)
  {
    iptoa(ip, (char*)buffer);
    memcpy(ipaddr, ip, 4);
  }
  else
  {
    strcat_P((char*)buffer, PSTR("192.168.0.1"));
    ipaddr[0] = 192;
    ipaddr[1] = 168;
    ipaddr[2] = 0;
    ipaddr[3] = 1;
  }
  if(netmask)
  {
    strcat_P((char*)buffer, PSTR(","));
    len = strlen((char*)buffer);
    iptoa(netmask, (char*)&buffer[len]);
  }
  else
  {
    strcat_P((char*)buffer, PSTR(",255.255.255.0"));
  }
  if(gateway)
  {
    strcat_P((char*)buffer, PSTR(","));
    len = strlen((char*)buffer);
    iptoa(gateway, (char*)&buffer[len]);
  }

  return cmd(PSTR(CMD_IPCONF "0,"), (char*)buffer); //xxx.xxx.xxx.xxx,yyy.yyy.yyy.yyy,zzz.zzz.zzz.zzz
}

uint8_t REDFLY::begin(uint8_t *ip, uint8_t *dns, uint8_t *gateway, uint8_t *netmask) { return begin(   0, ip, dns, gateway, netmask); }
uint8_t REDFLY::begin(uint8_t *ip, uint8_t *dns, uint8_t *gateway)                   { return begin(   0, ip, dns, gateway,       0); }
uint8_t REDFLY::begin(uint8_t *ip, uint8_t *dns)                                     { return begin(   0, ip, dns,       0,       0); }
uint8_t REDFLY::begin(uint8_t *ip)                                                   { return begin(   0, ip,   0,       0,       0); }
uint8_t REDFLY::begin(uint8_t dhcp)                                                  { return begin(dhcp,  0,   0,       0,       0); }
uint8_t REDFLY::begin(void)                                                          { return begin(   1,  0,   0,       0,       0); }

    
uint8_t REDFLY::socketConnect(uint8_t proto, uint8_t *ip, uint16_t port, uint16_t lport)
{
  uint8_t ret=INVALID_SOCKET, len;

  //ip
  iptoa(ip, (char*)buffer); 
  //port
  strcat_P((char*)buffer, PSTR(","));
  len = strlen((char*)buffer);
  uitoa(port, (char*)&buffer[len]);
  //local port
  strcat_P((char*)buffer, PSTR(","));
  len = strlen((char*)buffer);
  uitoa(lport, (char*)&buffer[len]);

  if(proto == PROTO_MCAST) //Multicast
  {
    proto = SOCKET_MCAST;
    if(cmd(buffer, 8, PSTR(CMD_MCAST), (char*)buffer) == 0) //xxx.xxx.xxx.xxx,aaaaa,bbbbb
    {
      ret = buffer[2]; //OKx
    }
  }
  else if(proto == PROTO_TCP) //TCP
  {
    proto = SOCKET_TCP;
    if(cmd(buffer, 8, PSTR(CMD_TCP), (char*)buffer) == 0) //xxx.xxx.xxx.xxx,aaaaa,bbbbb
    {
      ret = buffer[2]; //OKx
    }
  }
  else //UDP
  {
    proto = SOCKET_UDP;
    if(cmd(buffer, 8, PSTR(CMD_UDP), (char*)buffer) == 0) //xxx.xxx.xxx.xxx,aaaaa,bbbbb
    {
      ret = buffer[2]; //OKx
    }
  }

  if(ret != INVALID_SOCKET) //handle okay -> save socket handle and type
  {
    for(uint8_t i=0; i<MAX_SOCKETS; i++)
    {
      if(socket_state[i].handle == INVALID_SOCKET)
      {
        socket_state[i].handle = ret;
        socket_state[i].state  = proto;
        break;
      }
    }
  }

  return ret;
}


uint8_t REDFLY::socketConnect(uint8_t proto, uint8_t *ip, uint16_t port)
{
  static uint16_t lport=1024;

  if(++lport > 2048)
  {
    lport = 1024;
  }

  return socketConnect(proto, ip, port, lport);
}


uint8_t REDFLY::socketListen(uint8_t proto, uint16_t lport)
{
  uint8_t ret=INVALID_SOCKET;

  //local port
  uitoa(lport, (char*)&buffer[0]);

  if(proto == PROTO_TCP) //TCP
  {
    proto = SOCKET_TCP;
    if(cmd(buffer, sizeof(buffer), PSTR(CMD_LTCP), (char*)buffer) == 0)
    {
      ret = buffer[2]; //OKx
    }
  }
  else //UDP
  {
    proto = SOCKET_UDP;
    if(cmd(buffer, sizeof(buffer), PSTR(CMD_LUDP), (char*)buffer) == 0)
    {
      ret = buffer[2]; //OKx
    }
  }

  if(ret != INVALID_SOCKET) //handle okay -> save socket handle and type
  {
    for(uint8_t i=0; i<MAX_SOCKETS; i++)
    {
      if(socket_state[i].handle == INVALID_SOCKET)
      {
        socket_state[i].handle = ret;
        socket_state[i].state  = proto;
        break;
      }
    }
  }

  return ret;
}


uint8_t REDFLY::socketClose(uint8_t socket)
{
  uint8_t ret=0;

  while(available()) //check for new data, if socket already closed?
  {
    uint8_t sock=INVALID_SOCKET;
    uint16_t len=0;
    socketRead(&sock, &len, 0, 0, 0, 0);
    if(sock == socket)
    {
      while(len) //clear buffer
      {
        uint8_t b[8];
        sock = socket;
        socketRead(&sock, &len, 0, 0, b, 8);
      }
    }
    else
    {
      break;
    }
  }

  //close socket if opened
  if(socket != INVALID_SOCKET)
  {
    for(uint8_t i=0; i<MAX_SOCKETS; i++)
    {
      if(socket_state[i].handle == socket)
      {
        socket_state[i].handle = INVALID_SOCKET;
        socket_state[i].state  = SOCKET_CLOSED;
        for(i=3; i!=0; i--) //try 3 times
        {
          ret = cmd(PSTR(CMD_CLS), socket);
          if((ret == 0) || (ret == 0xFE)) //(0xFE = socket already closed)
          {
            ret = 0;
            break;
          }
        }
        break;
      }
    }
  }

  return ret;
}


uint8_t REDFLY::socketClosed(uint8_t socket)
{
  if(available()) //check for new data, if socket closed?
  {
    uint8_t sock=INVALID_SOCKET;
    uint16_t len=0;
    socketRead(&sock, &len, 0, 0, 0, 0);
  }

  if(socket != INVALID_SOCKET)
  {
    for(uint8_t i=0; i<MAX_SOCKETS; i++)
    {
      if(socket_state[i].handle == socket) //socket found
      {
        return 0;
      }
    }
  }

  return 1;
}


uint8_t REDFLY::socketStatus(uint8_t socket)
{
  if(available()) //check for new data, if socket closed?
  {
    uint8_t sock=INVALID_SOCKET;
    uint16_t len=0;
    socketRead(&sock, &len, 0, 0, 0, 0);
  }

  for(uint8_t i=0; i<MAX_SOCKETS; i++)
  {
    if(socket_state[i].handle == socket)
    {
      return cmd(PSTR(CMD_CTCP), socket);
    }
  }

  return 0xFF;
}


uint8_t REDFLY::socketState(uint8_t socket)
{
  for(uint8_t i=0; i<MAX_SOCKETS; i++)
  {
    if(socket_state[i].handle == socket)
    {
      return socket_state[i].state;
    }
  }

  return SOCKET_CLOSED;
}


uint8_t REDFLY::socketSend(uint8_t socket, uint8_t *stream, uint16_t size, uint8_t *ip, uint16_t port)
{
  uint8_t len;

  //socket
  uitoa(socket, (char*)buffer);
  //size
  strcat_P((char*)buffer, PSTR(","));
  len = strlen((char*)buffer);
  uitoa(size, (char*)&buffer[len]);
  //ip
  if(ip && (socketState(socket) == SOCKET_UDP))
  {
    strcat_P((char*)buffer, PSTR(","));
    len = strlen((char*)buffer);
    iptoa(ip, (char*)&buffer[len]);
  }
  else
  {
    strcat_P((char*)buffer, PSTR(",0"));
  }
  //port
  if(port && (socketState(socket) == SOCKET_UDP))
  {
    strcat_P((char*)buffer, PSTR(","));
    len = strlen((char*)buffer);
    uitoa(port, (char*)&buffer[len]);
  }
  else
  {
    strcat_P((char*)buffer, PSTR(",0"));
  }
  //data
  strcat_P((char*)buffer, PSTR(","));

  return cmd(PSTR(CMD_SEND), (char*)buffer, stream, size); //x,xxxx,xxx.xxx.xxx.xxx,xxxxx,
}


uint8_t REDFLY::socketSend(uint8_t socket, char *stream, uint8_t *ip, uint16_t port)
{
  return socketSend(socket, (uint8_t*)stream, strlen(stream), ip, port);
}


uint8_t REDFLY::socketSendPGM(uint8_t socket, PGM_P stream, uint8_t *ip, uint16_t port)
{
  uint8_t len;
  uint16_t size = strlen_P(stream);

  //socket
  uitoa(socket, (char*)buffer);
  //size
  strcat_P((char*)buffer, PSTR(","));
  len = strlen((char*)buffer);
  uitoa(size, (char*)&buffer[len]);
  //ip
  if(ip && (socketState(socket) == SOCKET_UDP))
  {
    strcat_P((char*)buffer, PSTR(","));
    len = strlen((char*)buffer);
    iptoa(ip, (char*)&buffer[len]);
  }
  else
  {
    strcat_P((char*)buffer, PSTR(",0"));
  }
  //port
  if(port && (socketState(socket) == SOCKET_UDP))
  {
    strcat_P((char*)buffer, PSTR(","));
    len = strlen((char*)buffer);
    uitoa(port, (char*)&buffer[len]);
  }
  else
  {
    strcat_P((char*)buffer, PSTR(",0"));
  }
  //data
  strcat_P((char*)buffer, PSTR(","));

  return cmd(PSTR(CMD_SEND), (char*)buffer, stream); //x,xxxx,xxx.xxx.xxx.xxx,xxxxx,
}


uint8_t REDFLY::socketSend(uint8_t socket, uint8_t *stream, uint16_t size)
{
  return socketSend(socket, stream, size, 0, 0);
}


uint8_t REDFLY::socketSend(uint8_t socket, char *stream)
{
  return socketSend(socket, (uint8_t*)stream, strlen(stream), 0, 0);
}


uint8_t REDFLY::socketSendPGM(uint8_t socket, PGM_P stream)
{
  return socketSendPGM(socket, stream, 0, 0);
}


uint8_t REDFLY::socketSend(uint8_t socket, int val)
{
  char buf[8];

  itoa(val, buf, 10);

  return socketSend(socket, (uint8_t*)buf, strlen(buf), 0, 0);
}


uint16_t REDFLY::socketRead(uint8_t *socket, uint16_t *len, uint8_t *ip, uint16_t *port, uint8_t *dst, uint16_t dst_size)
{
  uint8_t stop=0;
  uint16_t rd=0;
  static uint8_t last_socket=INVALID_SOCKET;
  static uint16_t last_len=0;
  static uint8_t buf[8], pos=0;
  static uint16_t udp_port=0;
  static uint8_t udp_ip[4];

  if(read_state == 2) //we are currently reading data
  {
    if((*socket != INVALID_SOCKET) && (*socket != last_socket)) //abort if not searched socket
    {
      return 0;
    }
    if(dst_size == 0) //only get len and socket
    {
      *socket = last_socket;
      *len    = last_len;
      return 0;
    }
  }

  do
  {
    switch(read_state)
    {
      case 0: //restart searching
        read_state  = 1;
        last_socket = INVALID_SOCKET;
        last_len    = 0;
        pos         = 0;
        udp_port    = 0;
        udp_ip[0]   = 0;
        udp_ip[1]   = 0;
        udp_ip[2]   = 0;
        udp_ip[3]   = 0;

      case 1: //search
        while((pos<8) && available())
        {
          buf[pos++] = read();
        }
        if(pos >= 8)
        {
          if((buf[0] == 'R') && \
             (buf[1] == 'S') && \
             (buf[2] == 'I') && \
             (buf[3] == '_') && \
             (buf[4] == 'R') && \
             (buf[5] == 'E') && \
             (buf[6] == 'A') && \
             (buf[7] == 'D')) //RSI_READ
          {
            last_socket = readwait();
            last_len    = readwait();
            last_len   |= readwait()<<8;

            if((last_socket == INVALID_SOCKET) || (last_len == 0))
            {
              read_state  = 0;
              last_socket = INVALID_SOCKET;
              last_len    = 0;
              break;
            }
            read_state  = 2;

            //get IP and port on UDP connection
            if(socketState(last_socket) == SOCKET_UDP)
            {
              udp_ip[0] = readwait();
              udp_ip[1] = readwait();
              udp_ip[2] = readwait();
              udp_ip[3] = readwait();
              udp_port  = readwait();
              udp_port |= readwait()<<8;
            }

            if((*socket != INVALID_SOCKET) && (*socket != last_socket)) //abort if not searched socket
            {
              return 0;
            }
            if(dst_size == 0)
            {
              stop = 1; //break loop
            }
          }
          else if((buf[0] == 'S') && \
                  (buf[1] == 'I') && \
                  (buf[2] == '_') && \
                  (buf[3] == 'C') && \
                  (buf[4] == 'L') && \
                  (buf[5] == 'O') && \
                  (buf[6] == 'S') && \
                  (buf[7] == 'E')) //SI_CLOSE
          {
            last_socket = readwait();
            readwait(); readwait(); //trailing \r\n
            last_len    = 0;
            rd          = 0xFFFF;
            read_state  = 0;
            stop        = 1; //break loop
            for(uint8_t i=0; i<MAX_SOCKETS; i++)
            {
              if(socket_state[i].handle == last_socket)
              {
                socket_state[i].handle = INVALID_SOCKET;
                socket_state[i].state  = SOCKET_CLOSED;
                break;
              }
            }
          }
          else
          {
            //move one byte
            pos = 7;
            buf[0] = buf[1];
            buf[1] = buf[2];
            buf[2] = buf[3];
            buf[3] = buf[4];
            buf[4] = buf[5];
            buf[5] = buf[6];
            buf[6] = buf[7];
          }
        }
        break;

      case 2: //receive
        *dst = readwait();
        dst_size--;
        rd++;
        if(--last_len == 0)
        {
          readwait(); readwait(); //trailing \r\n
          read_state = 0;
          stop       = 1; //break loop
        }
        else if(dst_size == 0)
        {
          stop       = 1; //break loop
        }
        break;
    }
  }while(available() && (stop == 0));

  *socket = last_socket;
  *len    = last_len;
  if(ip && udp_ip[0])
  {
    ip[0] = udp_ip[0];
    ip[1] = udp_ip[1];
    ip[2] = udp_ip[2];
    ip[3] = udp_ip[3];
  }
  if(port && udp_port)
  {
    *port = udp_port;
  }

  return rd;
}


uint16_t REDFLY::socketRead(uint8_t *socket, uint16_t *len, uint8_t *dst, uint16_t dst_size) //TCP connection
{
  return socketRead(socket, len, 0, 0, dst, dst_size);
}


void REDFLY::socketReset(void)
{
  read_state = 0;

  for(uint8_t i=0; i<MAX_SOCKETS; i++)
  {
    socket_state[i].handle = INVALID_SOCKET;
    socket_state[i].state  = SOCKET_CLOSED;
  }

  flush();

  return;
}


//-------------------- Private --------------------


uint8_t REDFLY::cmd(uint8_t *dst, uint8_t dst_size, PGM_P p1, char *v1, PGM_P p2, uint8_t *v2, uint16_t v2_size)
{
  uint8_t c, i;
  uint32_t ms;
  uint32_t timeout;
  uint8_t buf[8]; //ERRORx

  if(read_state == 2) //currently receiving data?
  {
    return 0xFF;
  }
  else if(available()) //check for new data
  {
    uint8_t sock=INVALID_SOCKET;
    uint16_t len=0;
    socketRead(&sock, &len, 0, 0, 0, 0);
    if(len != 0) //rx data found
    {
      return 0xFF;
    }
  }

  //send p1 command
  c = pgm_read_byte(p1++);
  while(c != 0)
  {
    write(c);
    c = pgm_read_byte(p1++);
  }

  //send v1 parameter 1
  if(v1)
  {
    while(*v1)
    {
      write(*v1++);
    }
  }

  //send p2 parameter 2
  if(p2)
  {
    c = pgm_read_byte(p2++);
    while(c != 0)
    {
      if(c == 0xDB) //0xDB -> 0xDB 0xDD
      {
        write(0xDB);
        write(0xDD);
        c = pgm_read_byte(p2++);
      }
      else if((c == 0x0D) && (pgm_read_byte(p2) == 0x0A)) //\r\n -> 0xDB 0xDC
      {
        write(0xDB);
        write(0xDC);
        p2++;
        c = pgm_read_byte(p2++);
      }
      else
      {
        write(c);
        c = pgm_read_byte(p2++);
      }
    }
  }

  //send v2 parameter 3
  if(v2_size)
  {
    while(v2_size)
    {
      if(v2[0] == 0xDB) //0xDB -> 0xDB 0xDD
      {
        write(0xDB);
        write(0xDD);
        v2++; v2_size--;
      }
      else if((v2[0] == 0x0D) && (v2[1] == 0x0A) && (v2_size >= 2)) //\r\n -> 0xDB 0xDC
      {
        write(0xDB);
        write(0xDC);
        v2+=2; v2_size-=2;
      }
      else
      {
        write(*v2++);
        v2_size--;
      }
    }
  }

  //flush rx and tx buffer
  flush_nowait();

  //send end characters of command
  write('\r');
  write('\n');

  //read response
  timeout = 10000; //default timeout: 10s
  if(dst_size == 0) //dont save response
  {
    buf[0] = 0;
    buf[5] = 0;
    for(i=0, ms=millis(); (millis()-ms) < timeout;)
    {
      if(available())
      {
        c = read();
        if(i < 8)
        {
          buf[i++] = c;
          if((buf[0] != 'O') && (buf[0] != 'E')) //OK or ERROR
          {
            i = 0;
          }
        }
        ms = millis();
        timeout = 3; //3 ms timeout
      }
    }
  }
  else //save response to dst
  {
    dst[0] = 0;
    dst[5] = 0;
    for(i=0, ms=millis(); (millis()-ms) < timeout;)
    {
      if(available())
      {
        c = read();
        if(i < dst_size)
        {
          dst[i++] = c;
          if((dst[0] != 'O') && (dst[0] != 'E')) //OK or ERROR
          {
            i = 0;
          }
        }
        ms = millis();
        timeout = 3; //3 ms timeout
      }
    }
    buf[0] = dst[0];
    buf[1] = dst[1];
    buf[5] = dst[5];
  }

  //check response
  if((buf[0] == 'O') && (buf[1] == 'K'))
  {
    return 0; //OK
  }
  else if((buf[0] == 'E') && (buf[1] == 'R') && (buf[5] != 0) && (buf[5] != '\r'))
  {
    return buf[5]; //ERROR code
  }

  return 0xFF;
}


uint8_t REDFLY::cmd(uint8_t *dst, uint8_t dst_size, PGM_P p1, int16_t val)
{
  char buf[8];

  itoa(val, buf, 10);

  return cmd(dst, dst_size, p1, buf, 0, 0, 0);
}

uint8_t REDFLY::cmd(uint8_t *dst, uint8_t dst_size, PGM_P p1, uint8_t *v2, uint16_t v2_size)           { return cmd(dst, dst_size, p1, 0,  0,  v2, v2_size); }
uint8_t REDFLY::cmd(uint8_t *dst, uint8_t dst_size, PGM_P p1, char *v1)                                { return cmd(dst, dst_size, p1, v1,  0,  0,       0); }
uint8_t REDFLY::cmd(uint8_t *dst, uint8_t dst_size, PGM_P p1)                                          { return cmd(dst, dst_size, p1,  0,  0,  0,       0); }
uint8_t REDFLY::cmd(                                PGM_P p1, char *v1, PGM_P p2)                      { return cmd(  0,        0, p1, v1, p2,  0,       0); }
uint8_t REDFLY::cmd(                                PGM_P p1, char *v1, uint8_t *v2, uint16_t v2_size) { return cmd(  0,        0, p1, v1,  0, v2, v2_size); }
uint8_t REDFLY::cmd(                                PGM_P p1, char *v1)                                { return cmd(  0,        0, p1, v1,  0,  0,       0); }
uint8_t REDFLY::cmd(                                PGM_P p1, int16_t v1)                              { return cmd(  0,        0, p1, v1                 ); }
uint8_t REDFLY::cmd(                                PGM_P p1)                                          { return cmd(  0,        0, p1,  0,  0,  0,       0); }


void REDFLY::flush(void)
{
  uint32_t ms;

  //clear tx buffer
  _SERIAL_.flush();

  //clear rx buffer
#if defined(__AVR__)
  for(ms=millis(); ((_UCSRA_&(1<<_RXC_)) || available()) && ((millis()-ms) < 50);) //50ms
#else
  for(ms=millis(); available() && ((millis()-ms) < 50);) //50ms
#endif
  {
    read();
  }
  delay_10ms(1);

  return;
}


void REDFLY::flush_nowait(void)
{
  //clear tx buffer
  _SERIAL_.flush();

  //clear rx buffer
  for(int len=available(); len!=0; len--)
  {
    read();
  }

  return;
}


int REDFLY::available(void)
{
  return _SERIAL_.available();
}


uint8_t REDFLY::readwait(void) //serial read
{
  while(!available());

  return (uint8_t)_SERIAL_.read();
}


uint8_t REDFLY::read(void) //serial read
{
  return _SERIAL_.read();
}


void REDFLY::write(uint8_t c) //serial write
{
  _SERIAL_.write(c);

  return;
}


void REDFLY::setbaudrate(uint32_t br) //set serial baudrate and config (8n2)
{
  if(br < 9600)
  {
    br = 9600;
  }
  else if(br > 3686400)
  {
    br = 3686400;
  }

  _SERIAL_.begin(br);

  //8 N 2
#if defined(__AVR__)
  _UCSRC_ |= (1<<_USBS_);
#else
  _USART_->US_MR |= US_MR_NBSTOP_2_BIT;
  //_USART_->US_MR = US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_CHRL_8_BIT | US_MR_PAR_NO | US_MR_NBSTOP_2_BIT | US_MR_CHMODE_NORMAL;
#endif

  return;
}


char* REDFLY::iptoa(uint8_t *ip, char *s) //convert ip to string
{
  sprintf_P(s, PSTR("%i.%i.%i.%i"), ip[0], ip[1], ip[2], ip[3]);

  return s;
}


char* REDFLY::uitoa(uint16_t val, char *s) //convert unsigned int to string
{
  sprintf_P(s, PSTR("%u"), val);

  return s;
}


void REDFLY::delay_10ms(uint8_t ms) //delay of 10ms * x
{
  for(; ms!=0; ms--)
  {
#if defined(__AVR__)
    _delay_ms(10);
#else
    delay(10);
#endif
  }

  return;
}
