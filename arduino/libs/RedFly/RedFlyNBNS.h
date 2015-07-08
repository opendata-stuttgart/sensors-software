#ifndef REDFLYNBNS_h
#define REDFLYNBNS_h


#include <inttypes.h>
#if defined(__AVR__)
# include <avr/pgmspace.h>
#endif
#include "RedFlyServer.h"


class RedFlyNBNS : RedFlyServer
{
  public:
    RedFlyNBNS(void);
    RedFlyNBNS(char *name);
    ~RedFlyNBNS(void);

    void setName(char *name);
#if defined(__AVR__)
    void setNamePGM(PGM_P name);
#endif
    uint8_t service(void);

  private:
    char devname[16+1];

    uint8_t decode(char *dst, char *src);
    void encode(char *dst, char *src, uint8_t type);
};


#endif //REDFLYNBNS_h
