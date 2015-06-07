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
#include "RedFlyServer.h"


#define MAX_ERRORS (10)


//-------------------- Constructor/Destructor --------------------


RedFlyServer::RedFlyServer(void) 
{
  s_port   = 80;
  s_socket = INVALID_SOCKET;

  return;
}


RedFlyServer::RedFlyServer(uint16_t port)
{
  s_port   = port;
  s_socket = INVALID_SOCKET;

  return;
}


RedFlyServer::~RedFlyServer(void) 
{
  stop();

  return;
}


//-------------------- Public --------------------


void RedFlyServer::begin(void)
{
  connectSocket(PROTO_TCP);

  return;
}


void RedFlyServer::beginUDP(void)
{
  connectSocket(PROTO_UDP);

  return;
}


int RedFlyServer::connect(void)
{
  return connectSocket(PROTO_TCP);
}


int RedFlyServer::connectUDP(void)
{
  return connectSocket(PROTO_UDP);
}


int RedFlyServer::connect(uint16_t port)
{
  s_port = port;

  return connectSocket(PROTO_TCP);
}


int RedFlyServer::connectUDP(uint16_t port)
{
  s_port = port;

  return connectSocket(PROTO_UDP);
}


int RedFlyServer::connectSocket(uint8_t p)
{
  if(s_socket != INVALID_SOCKET)
  {
    return 0;
  }

  s_socket = RedFly.socketListen(p, s_port);

  if(s_socket == INVALID_SOCKET)
  {
    return 0;
  }

  c_ip[0] = 0;
  c_ip[1] = 0;
  c_ip[2] = 0;
  c_ip[3] = 0;
  c_port  = 0;
  proto   = p;
  error   = 0;

  return 1;
}


uint8_t RedFlyServer::connected(void)
{
  if(s_socket == INVALID_SOCKET)
  {
    return 0;
  }

  if(RedFly.socketClosed(s_socket)) //socket closed?
  {
    s_socket = INVALID_SOCKET;
    return 0;
  }

  if(error >= MAX_ERRORS)
  {
    RedFly.socketClose(s_socket);
    s_socket = INVALID_SOCKET;
    return 0;
  }

  return 1;
}


void RedFlyServer::stop(void)
{
  if(s_socket == INVALID_SOCKET)
  {
    return;
  }

  flush(); //clear buffer

  RedFly.socketClose(s_socket);
  s_socket = INVALID_SOCKET;
  error    = 0;

  return;
}


uint8_t RedFlyServer::status(void)
{
  if(s_socket == INVALID_SOCKET)
  {
    return 1;
  }

  if(RedFly.socketStatus(s_socket)) //socket closed?
  {
    s_socket = INVALID_SOCKET;
    return 1;
  }

  return 0;
}


uint8_t RedFlyServer::getsocket(void)
{
  return s_socket;
}


void RedFlyServer::getip(uint8_t *ip)
{
  ip[0] = c_ip[0];
  ip[1] = c_ip[1];
  ip[2] = c_ip[2];
  ip[3] = c_ip[3];

  return;
}


uint16_t RedFlyServer::getport(void)
{
  return c_port;
}


int RedFlyServer::available(void)
{
  uint8_t socket=s_socket;
  uint16_t len=0;

  if(socket != INVALID_SOCKET)
  {
    RedFly.socketRead(&socket, &len, 0, 0);
  }

  return (int)len;
}


int RedFlyServer::read(void)
{
  uint8_t b;
  uint8_t socket=s_socket;
  uint16_t len, rd;

  if(socket == INVALID_SOCKET)
  {
    return -1;
  }

  if(RedFly.socketState(socket) == SOCKET_UDP)
  {
    rd = RedFly.socketRead(&socket, &len, c_ip, &c_port, &b, 1);
  }
  else
  {
    rd = RedFly.socketRead(&socket, &len, &b, 1);
  }
  if(rd == 0)
  {
    return -1;
  }
  if(rd == 0xFFFF) //socket closed?
  {
    s_socket = INVALID_SOCKET;
    return -1;
  }

  return b;
}


int RedFlyServer::read(uint8_t *s, size_t sz)
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


void RedFlyServer::flush(void)
{
  for(int len=available(); len!=0; len--)
  {
    read();
  }

  return;
}


size_t RedFlyServer::write(uint8_t b) 
{
  if(s_socket != INVALID_SOCKET)
  {
    if(RedFly.socketSend(s_socket, (uint8_t*)&b, 1, c_ip, c_port))
    {
      if(++error >= MAX_ERRORS)
      {
        RedFly.socketClose(s_socket);
        s_socket = INVALID_SOCKET;
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


size_t RedFlyServer::write(const char *s) 
{
  if(s_socket != INVALID_SOCKET)
  {
    if(RedFly.socketSend(s_socket, (char*)s, c_ip, c_port))
    {
      if(++error >= MAX_ERRORS)
      {
        RedFly.socketClose(s_socket);
        s_socket = INVALID_SOCKET;
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


size_t RedFlyServer::write(const uint8_t *s, size_t size) 
{
  if(s_socket != INVALID_SOCKET)
  {
    if(RedFly.socketSend(s_socket, (uint8_t*)s, size, c_ip, c_port))
    {
      if(++error >= MAX_ERRORS)
      {
        RedFly.socketClose(s_socket);
        s_socket = INVALID_SOCKET;
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


size_t RedFlyServer::print_P(PGM_P s)
{
  if(s_socket != INVALID_SOCKET)
  {
    if(RedFly.socketSendPGM(s_socket, s, c_ip, c_port))
    {
      if(++error >= MAX_ERRORS)
      {
        RedFly.socketClose(s_socket);
        s_socket = INVALID_SOCKET;
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


size_t RedFlyServer::println_P(PGM_P s)
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
RedFlyServer::operator bool()
{
  return s_socket != INVALID_SOCKET;
}
