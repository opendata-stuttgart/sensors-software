#include <inttypes.h>
#if defined(__AVR__)
# include <avr/pgmspace.h>
#endif
#if ARDUINO >= 100
# include "Arduino.h"
#else
# include "WProgram.h"
#endif
#include "RedFly.h"
#include "RedFlyClient.h"


#define MAX_ERRORS (10)


//-------------------- Constructor/Destructor --------------------


RedFlyClient::RedFlyClient(void)
{
  c_port   = 0;
  c_socket = INVALID_SOCKET;

  return;
}


RedFlyClient::RedFlyClient(uint8_t socket)
{
  c_port   = 0;
  c_socket = socket;

  return;
}


RedFlyClient::RedFlyClient(uint8_t *ip, uint16_t port)
{
  c_ip[0]  = ip[0];
  c_ip[1]  = ip[1];
  c_ip[2]  = ip[2];
  c_ip[3]  = ip[3];
  c_port   = port;
  c_socket = INVALID_SOCKET;

  return;
}


RedFlyClient::RedFlyClient(uint8_t *ip, uint16_t port, uint16_t lport)
{
  c_ip[0]  = ip[0];
  c_ip[1]  = ip[1];
  c_ip[2]  = ip[2];
  c_ip[3]  = ip[3];
  c_port   = port;
  c_lport  = lport;
  c_socket = INVALID_SOCKET;

  return;
}


RedFlyClient::~RedFlyClient(void)
{
  stop();

  return;
}


//-------------------- Public --------------------


void RedFlyClient::begin(void)
{
  connectSocket(PROTO_TCP);

  return;
}


void RedFlyClient::beginUDP(void)
{
  connectSocket(PROTO_UDP);

  return;
}


int RedFlyClient::connect(void)
{
  return connectSocket(PROTO_TCP);
}


int RedFlyClient::connectUDP(void)
{
  return connectSocket(PROTO_UDP);
}


int RedFlyClient::connect(uint8_t *ip, uint16_t port)
{
  c_ip[0] = ip[0];
  c_ip[1] = ip[1];
  c_ip[2] = ip[2];
  c_ip[3] = ip[3];
  c_port  = port;

  return connectSocket(PROTO_TCP);
}


int RedFlyClient::connectUDP(uint8_t *ip, uint16_t port)
{
  c_ip[0] = ip[0];
  c_ip[1] = ip[1];
  c_ip[2] = ip[2];
  c_ip[3] = ip[3];
  c_port  = port;

  return connectSocket(PROTO_UDP);
}


int RedFlyClient::connect(uint8_t *ip, uint16_t port, uint16_t lport)
{
  c_ip[0] = ip[0];
  c_ip[1] = ip[1];
  c_ip[2] = ip[2];
  c_ip[3] = ip[3];
  c_port  = port;
  c_lport = lport;

  return connectSocket(PROTO_TCP);
}


int RedFlyClient::connectUDP(uint8_t *ip, uint16_t port, uint16_t lport)
{
  c_ip[0] = ip[0];
  c_ip[1] = ip[1];
  c_ip[2] = ip[2];
  c_ip[3] = ip[3];
  c_port  = port;
  c_lport = lport;

  return connectSocket(PROTO_UDP);
}


int RedFlyClient::connect(char *host, uint16_t port)
{
  if(RedFly.getip(host, c_ip) == 0)
  {
    c_port  = port;
    return connectSocket(PROTO_TCP);
  }

  return 0;
}


int RedFlyClient::connectUDP(char *host, uint16_t port)
{
  if(RedFly.getip(host, c_ip) == 0)
  {
    c_port  = port;
    return connectSocket(PROTO_UDP);
  }

  return 0;
}


int RedFlyClient::connectSocket(uint8_t p)
{
  if(c_socket != INVALID_SOCKET)
  {
    return 0;
  }

  if(c_lport)
  {
    c_socket = RedFly.socketConnect(p, c_ip, c_port, c_lport);
  }
  else
  {
    c_socket = RedFly.socketConnect(p, c_ip, c_port);
  }

  if(c_socket == INVALID_SOCKET)
  {
    return 0;
  }

  proto = p;
  error = 0;

  return 1;
}


uint8_t RedFlyClient::connected(void)
{
  if(c_socket == INVALID_SOCKET)
  {
    return 0;
  }

  if(RedFly.socketClosed(c_socket)) //socket closed?
  {
    c_socket = INVALID_SOCKET;
    return 0;
  }

  if(error >= MAX_ERRORS)
  {
    RedFly.socketClose(c_socket);
    c_socket = INVALID_SOCKET;
    return 0;
  }

  return 1;
}


void RedFlyClient::stop(void)
{
  if(c_socket == INVALID_SOCKET)
  {
    return;
  }

  flush(); //clear buffer

  RedFly.socketClose(c_socket);
  c_socket = INVALID_SOCKET;
  error    = 0;

  return;
}


uint8_t RedFlyClient::status(void)
{
  if(c_socket == INVALID_SOCKET)
  {
    return 1;
  }

  if(RedFly.socketStatus(c_socket)) //socket closed?
  {
    c_socket = INVALID_SOCKET;
    return 1;
  }

  return 0;
}


uint8_t RedFlyClient::getsocket(void)
{
  return c_socket;
}


int RedFlyClient::available(void)
{
  uint8_t socket=c_socket;
  uint16_t len=0;

  if(socket != INVALID_SOCKET)
  {
    RedFly.socketRead(&socket, &len, 0, 0);
  }

  return (int)len;
}


int RedFlyClient::read(void)
{
  uint8_t b;
  uint8_t socket=c_socket;
  uint16_t len, rd;

  if(socket == INVALID_SOCKET)
  {
    return -1;
  }

  rd = RedFly.socketRead(&socket, &len, &b, 1);

  if(rd == 0)
  {
    return -1;
  }
  if(rd == 0xFFFF) //socket closed?
  {
    c_socket = INVALID_SOCKET;
    return -1;
  }
 
  return b;
}


int RedFlyClient::read(uint8_t *s, size_t sz)
{
  int c, rd;

  for(rd=0; sz;)
  {
    c = read();
    if(c != -1)
    {
      *s++ = (uint8_t)c;
      sz--;
      rd++;
    }
    else
    {
      break;
    }
  }

  return rd;
}


void RedFlyClient::flush(void)
{
  for(int len=available(); len!=0; len--)
  {
    read();
  }

  return;
}


size_t RedFlyClient::write(uint8_t b)
{
  if(c_socket != INVALID_SOCKET)
  {
    if(RedFly.socketSend(c_socket, (uint8_t*)&b, 1, c_ip, c_port))
    {
      if(++error >= MAX_ERRORS)
      {
        RedFly.socketClose(c_socket);
        c_socket = INVALID_SOCKET;
      }
    }
    else
    {
      error = 0;
      return 1;
    }
  }

  return 0;
}


size_t RedFlyClient::write(const char *s)
{
  if(c_socket != INVALID_SOCKET)
  {
    if(RedFly.socketSend(c_socket, (char*)s, c_ip, c_port))
    {
      if(++error >= MAX_ERRORS)
      {
        RedFly.socketClose(c_socket);
        c_socket = INVALID_SOCKET;
      }
    }
    else
    {
      error = 0;
      return strlen(s);
    }
  }

  return 0;
}


size_t RedFlyClient::write(const uint8_t *s, size_t size)
{
  if(c_socket != INVALID_SOCKET)
  {
    if(RedFly.socketSend(c_socket, (uint8_t*)s, size, c_ip, c_port))
    {
      if(++error >= MAX_ERRORS)
      {
        RedFly.socketClose(c_socket);
        c_socket = INVALID_SOCKET;
      }
    }
    else
    {
      error = 0;
      return size;
    }
  }

  return 0;
}


size_t RedFlyClient::print_P(PGM_P s)
{
  if(c_socket != INVALID_SOCKET)
  {
    if(RedFly.socketSendPGM(c_socket, s, c_ip, c_port))
    {
      if(++error >= MAX_ERRORS)
      {
        RedFly.socketClose(c_socket);
        c_socket = INVALID_SOCKET;
      }
    }
    else
    {
      error = 0;
      return strlen_P(s);
    }
  }

  return 0;
}


size_t RedFlyClient::println_P(PGM_P s)
{
  size_t len;

  len = print_P(s);
  if(len)
  {
    len += print_P(PSTR("\r\n"));
  }

  return len;
}


//the next function allows us to use the client returned by
//RedFlyServer::available() as the condition in an if-statement.
RedFlyClient::operator bool()
{
  return c_socket != INVALID_SOCKET;
}
