#ifndef REDFLY_h
#define REDFLY_h


#include <inttypes.h>
#if defined(__AVR__)
# include <avr/pgmspace.h>
#else
# define pgm_read_byte(addr)  (*(const uint8_t *)(addr))
# define pgm_read_word(addr)  (*(const uint16_t *)(addr))
# define pgm_read_dword(addr) (*(const uint32_t *)(addr))
# define PSTR(x)              (x)
# define PGM_P                const char*
# define strlen_P             strlen
# define strcpy_P             strcpy
# define strcat_P             strcat
# define strcmp_P             strcmp
# define strncmp_P            strncmp
# define strncasecmp_P        strncasecmp
# define sprintf_P            sprintf
#endif


//default baud rate
#define REDFLY_BAUDRATE (9600)

//Tx power (init cmd)
#define LOW_POWER       (0)
#define MED_POWER       (1)
#define HIGH_POWER      (2)
#define LOW_POWER_1M    (3)
#define MED_POWER_1M    (4)
#define HIGH_POWER_1M   (5)
#define LOW_POWER_2M    (6)
#define MED_POWER_2M    (7)
#define HIGH_POWER_2M   (8)
#define LOW_POWER_11M   (9)
#define MED_POWER_11M   (10)
#define HIGH_POWER_11M  (11)
#define LOW_POWER_12M   (12)
#define MED_POWER_12M   (13)
#define HIGH_POWER_12M  (14)
#define LOW_POWER_24M   (15)
#define MED_POWER_24M   (16)
#define HIGH_POWER_24M  (17)
#define LOW_POWER_54M   (18)
#define MED_POWER_54M   (19)
#define HIGH_POWER_54M  (20)

//net type (join cmd)
#define INFRASTRUCTURE  (0)
#define IBSS_JOINER     (1)
#define IBSS_CREATOR    (2)

//protocol (socket cmds)
#define PROTO_TCP       (0)
#define PROTO_UDP       (1)
#define PROTO_MCAST     (2)

//max. sockets (WiFi module supports up to 8 sockets and FW 4.7.1 only 7 sockets)
#define MAX_SOCKETS     (7)
#define INVALID_SOCKET  (0xFF)

//socket states
#define SOCKET_TCP      PROTO_TCP
#define SOCKET_UDP      PROTO_UDP
#define SOCKET_MCAST    PROTO_MCAST
#define SOCKET_CLOSED   (0xFF)

#ifndef SWAP16
#define SWAP16(x)       ((((x)&0x00FF)<<8)| \
                         (((x)&0xFF00)>>8))
#endif

#ifndef SWAP32
#define SWAP32(x)       ((((x)&0xFF000000UL)>>24)| \
                         (((x)&0x00FF0000UL)>> 8)| \
                         (((x)&0x0000FF00UL)<< 8)| \
                         (((x)&0x000000FFUL)<<24))
#endif


typedef struct 
{
	uint8_t handle;
	uint8_t state;
} SOCKET_STATE;


extern class REDFLY RedFly;

class REDFLY
{
  public:
    REDFLY(void);
    ~REDFLY(void);

    uint8_t init(uint32_t br, uint8_t pwr); //br=baudrate, pwr=tx_power
    uint8_t init(uint8_t pwr);              //pwr=tx_power
    uint8_t init(void);

    void enable(void);
    void disable(void);

    uint8_t getversion(char *ver);
    uint8_t getmac(uint8_t *mac); 
    uint8_t getlocalip(uint8_t *ip);
    uint8_t getip(char *host, uint8_t *ip);
    uint32_t gettime(uint8_t *server, uint16_t port);
    uint32_t gettime(uint8_t *server);
    uint8_t getrssi(void);
    uint8_t getbssid(char *ssid, uint8_t *mac);
    uint8_t gettype(char *ssid, uint8_t *type);

    uint8_t scan(void); 
    uint8_t scan(uint8_t chn, char *ssid, uint8_t *mode, uint8_t *rssi);  //returns: ssid, mode, rssi
    uint8_t scan(char *ssid, uint8_t *mode, uint8_t *rssi);               //returns: ssid, mode, rssi
    uint8_t scan(char *ssid);                                             //returns: ssid
    uint8_t nextscan(char *ssid, uint8_t *mode, uint8_t *rssi);           //returns: ssid, mode, rssi
    uint8_t nextscan(char *ssid);                                         //returns: ssid

    uint8_t join(char *ssid, char *key, uint8_t net, uint8_t chn, uint8_t authmode); //INFRASTRUCTURE or IBSS_JOINER or IBSS_CREATOR
    uint8_t join(char *ssid, char *key, uint8_t net, uint8_t chn); //IBSS_CREATOR
    uint8_t join(char *ssid, uint8_t net, uint8_t chn);            //IBSS_CREATOR
    uint8_t join(char *ssid, char *key, uint8_t net);              //INFRASTRUCTURE or IBSS_JOINER
    uint8_t join(char *ssid, uint8_t net);                         //INFRASTRUCTURE or IBSS_JOINER
    uint8_t join(char *ssid, char *key);                           //INFRASTRUCTURE
    uint8_t join(char *ssid);                                      //INFRASTRUCTURE

    uint8_t disconnect(void); //disassociate

    uint8_t begin(uint8_t dhcp, uint8_t *ip, uint8_t *dns, uint8_t *gateway, uint8_t *netmask);
    uint8_t begin(uint8_t *ip, uint8_t *dns, uint8_t *gateway, uint8_t *netmask); //dhcp off
    uint8_t begin(uint8_t *ip, uint8_t *dns, uint8_t *gateway);                   //dhcp off
    uint8_t begin(uint8_t *ip, uint8_t *dns);                                     //dhcp off
    uint8_t begin(uint8_t *ip);                                                   //dhcp off
    uint8_t begin(uint8_t dhcp);                                                  //dhcp or autoip
    uint8_t begin(void);                                                          //dhcp on

    uint8_t socketConnect(uint8_t proto, uint8_t *ip, uint16_t port, uint16_t lport); //ret 0xFF=error
    uint8_t socketConnect(uint8_t proto, uint8_t *ip, uint16_t port); //ret 0xFF=error (lport=1024...2048)

    uint8_t socketListen(uint8_t proto, uint16_t lport); //ret 0xFF=error

    uint8_t socketClose(uint8_t socket);
    uint8_t socketClosed(uint8_t socket); //0!=closed
    uint8_t socketStatus(uint8_t socket); //ret 0xFF=error
    uint8_t socketState(uint8_t socket); //ret 0xFF=closed

    uint8_t socketSend(uint8_t socket, uint8_t *stream, uint16_t size, uint8_t *ip, uint16_t port); //ip+port only for UDP
    uint8_t socketSend(uint8_t socket, char *stream, uint8_t *ip, uint16_t port); //ip+port only for UDP
    uint8_t socketSendPGM(uint8_t socket, PGM_P stream, uint8_t *ip, uint16_t port); //ip+port only for UDP
    uint8_t socketSend(uint8_t socket, uint8_t *stream, uint16_t size); //TCP
    uint8_t socketSend(uint8_t socket, char *stream);                   //TCP
    uint8_t socketSendPGM(uint8_t socket, PGM_P stream);                //TCP
    uint8_t socketSend(uint8_t socket, int value);                      //TCP

    uint16_t socketRead(uint8_t *socket, uint16_t *len, uint8_t *ip, uint16_t *port, uint8_t *dst, uint16_t dst_size); //ret 0xFFFF=closed
    uint16_t socketRead(uint8_t *socket, uint16_t *len, uint8_t *dst, uint16_t dst_size);
 
    void socketReset(void);

  private:
    uint8_t tx_power, read_state;
    uint8_t buffer[48]; //min. 48 (receive and data buffer)
    uint32_t baudrate;
    uint8_t ipaddr[4];
    SOCKET_STATE socket_state[MAX_SOCKETS];

    uint8_t cmd(uint8_t *dst, uint8_t dst_size, PGM_P p1, char *v1, PGM_P p2, uint8_t *v2, uint16_t v2_size);
    uint8_t cmd(uint8_t *dst, uint8_t dst_size, PGM_P p1, int16_t v1);
    uint8_t cmd(uint8_t *dst, uint8_t dst_size, PGM_P p1, uint8_t *v2, uint16_t v2_size);
    uint8_t cmd(uint8_t *dst, uint8_t dst_size, PGM_P p1, char *v1);
    uint8_t cmd(uint8_t *dst, uint8_t dst_size, PGM_P p1);
    uint8_t cmd(PGM_P p1, char *v1, PGM_P p2);
    uint8_t cmd(PGM_P p1, char *v1, uint8_t *v2, uint16_t v2_size);
    uint8_t cmd(PGM_P p1, char *v1);
    uint8_t cmd(PGM_P p1, int16_t v1);
    uint8_t cmd(PGM_P p1);

    void flush(void);
    void flush_nowait(void);
    int available(void);
    uint8_t readwait(void);
    uint8_t read(void);
    void write(uint8_t c);
    void setbaudrate(uint32_t br);
    char* iptoa(uint8_t *ip, char *s);
    char* uitoa(uint16_t val, char *s);
    void delay_10ms(uint8_t ms);
};


#endif //REDFLY_h
