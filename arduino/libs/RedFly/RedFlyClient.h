#ifndef REDFLYCLIENT_h
#define REDFLYCLIENT_h


#include <inttypes.h>
#if defined(__AVR__)
# include <avr/pgmspace.h>
#endif
#include "Print.h"
#include "RedFly.h"
#include "Server.h"


class RedFlyClient : public Server
{
  public:
    RedFlyClient(void);
    RedFlyClient(uint8_t socket);
    RedFlyClient(uint8_t *ip, uint16_t port);
    RedFlyClient(uint8_t *ip, uint16_t port, uint16_t lport);
    ~RedFlyClient(void);

    virtual void begin(void); //same as connect()
    virtual void beginUDP(void); //same as connect()
    virtual int connect(void);
    virtual int connectUDP(void);
    virtual int connect(uint8_t *ip, uint16_t port);
    virtual int connectUDP(uint8_t *ip, uint16_t port);
    virtual int connect(uint8_t *ip, uint16_t port, uint16_t lport);
    virtual int connectUDP(uint8_t *ip, uint16_t port, uint16_t lport);
    virtual int connect(char *host, uint16_t port);
    virtual int connectUDP(char *host, uint16_t port);
    int connectSocket(uint8_t p);
    virtual uint8_t connected(void);
    virtual void stop(void);
    uint8_t status(void);
    uint8_t getsocket(void);

    virtual int available(void);
    virtual int read(void);
    virtual int read(uint8_t *s, size_t sz);
    //virtual int peek(void); //not available
    virtual void flush(void);
    virtual size_t write(uint8_t b);
    virtual size_t write(const char *s);
    virtual size_t write(const uint8_t *s, size_t sz);
    virtual size_t print_P(PGM_P s);
    virtual size_t println_P(PGM_P s);

    virtual operator bool();

    using Print::write;

  private:
    uint8_t c_socket;
    uint8_t c_ip[4];
    uint16_t c_port;
    uint16_t c_lport;
    uint8_t proto, error;
};


#endif //REDFLYCLIENT_h
