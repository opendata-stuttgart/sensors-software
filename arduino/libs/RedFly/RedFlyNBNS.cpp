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
#include "RedFlyNBNS.h"


//NBNS Question
#define NBNSQ_PACKETLEN      (38)
#define NBNSQ_TYPE_NB        (0x0020)
#define NBNSQ_CLASS_IN       (0x0001)
typedef struct __attribute__((packed))
{
  uint8_t  len       :   8; // 8bit Len: 32
  char     name[33];        //33byte Name + null
  uint16_t type      :  16; //16bit Type
  uint16_t clas      :  16; //16bit Class
} NBNS_Question;

//NBNS Answer
#define NBNSA_PACKETLEN      (50)
#define NBNSA_TYPE_NB        (0x0020)
#define NBNSA_CLASS_IN       (0x0001)
typedef struct __attribute__((packed))
{
  uint8_t  len       :   8; // 8bit Len: 32
  char     name[33];        //33byte Name + null
  uint16_t type      :  16; //16bit Type
  uint16_t clas      :  16; //16bit Class
  uint32_t ttl       :  32; //32bit Time to live
  uint16_t rdlen     :  16; //16bit Data len
  uint16_t flags     :  16; //16bit Flags    - rdata
  uint8_t  addr[4];         //32bit IP Addr  - rdata
} NBNS_Answer;

//NBNS (NetBIOS Name Service)
#define NBNS_PORT            (137)
#define NBNS_PACKETLEN       (12)
#define NBNS_OPMASK          (0x7800)
#define NBNS_REPLYMASK       (0x000F)
#define NBNS_FLAG_RESPONSE   (1<<15)
#define NBNS_FLAG_QUERY      (0<<15)
#define NBNS_FLAG_AUTHORITY  (1<<10)
#define NBNS_OP_QUERY        (0<<11)
typedef struct __attribute__((packed))
{
  uint16_t id        :  16; //16bit Transaction ID
  uint16_t flags_op  :  16; //16bit Flags
  uint16_t qdcount   :  16; //16bit Question Entries
  uint16_t ancount   :  16; //16bit Answer RRs
  uint16_t nscount   :  16; //16bit Authority RRs
  uint16_t arcount   :  16; //16bit Additional RRs
  union
  {
    NBNS_Question qd;
    NBNS_Answer   an;
  } data;
} NBNS_Packet;


//-------------------- Constructor/Destructor --------------------


RedFlyNBNS::RedFlyNBNS(void) : RedFlyServer(NBNS_PORT)
{
  strcpy(devname, "REDFLY");

  return;
}


RedFlyNBNS::RedFlyNBNS(char *name) : RedFlyServer(NBNS_PORT)
{
  strcpy(devname, name);

  return;
}


RedFlyNBNS::~RedFlyNBNS(void)
{
  stop();

  return;
}


//-------------------- Public --------------------


void RedFlyNBNS::setName(char *name)
{
  strcpy(devname, name);

  return;
}


#if defined(__AVR__)
void RedFlyNBNS::setNamePGM(PGM_P name)
{
  strcpy_P(devname, name);

  return;
}
#endif


#define SWAP16(x) ((((x)&0x00FF)<<8)| \
                   (((x)&0xFF00)>>8))
#define SWAP32(x) ((((x)&0xFF000000UL)>>24)| \
                   (((x)&0x00FF0000UL)>> 8)| \
                   (((x)&0x0000FF00UL)<< 8)| \
                   (((x)&0x000000FFUL)<<24))
uint8_t RedFlyNBNS::service(void)
{
  uint16_t len;
  uint8_t buf[NBNS_PACKETLEN+NBNSA_PACKETLEN];
  NBNS_Packet *nbns;
  char name[16+1];
  uint8_t type;

  if(!connected()) //listening port still open?
  {
    stop(); //stop and reset server
    beginUDP(); //start server
    return 1;
  }

  //data available?
  len = available();
  if(len >= (NBNS_PACKETLEN+NBNSQ_PACKETLEN))
  {
    //read data
    read(buf, sizeof(buf));
    flush(); //flush input buffer
    //check data for NBNS header and question
    nbns = (NBNS_Packet*) buf;
    if((nbns->qdcount      == SWAP16(0x0001))         &&
       (nbns->data.qd.len  == 32)                     &&
       (nbns->data.qd.type == SWAP16(NBNSQ_TYPE_NB))  &&
       (nbns->data.qd.clas == SWAP16(NBNSQ_CLASS_IN))) //NBNS question
    {
      type = decode(name, nbns->data.qd.name);
      if((type == 0x00) && (strcasecmp(name, devname) == 0))//0x00 = Workstation
      {
        //create NBNS answer
        nbns->id            = nbns->id;
        nbns->flags_op      = SWAP16(NBNS_FLAG_RESPONSE|NBNS_FLAG_AUTHORITY);
        nbns->qdcount       = SWAP16(0x0000);
        nbns->ancount       = SWAP16(0x0001);
        nbns->nscount       = SWAP16(0x0000);
        nbns->arcount       = SWAP16(0x0000);
        nbns->data.an.len   = 32;
        nbns->data.an.type  = SWAP16(NBNSA_TYPE_NB);
        nbns->data.an.clas  = SWAP16(NBNSA_CLASS_IN);
        nbns->data.an.ttl   = SWAP32(3600); //time to live 3600 sec = 1 hour
        nbns->data.an.rdlen = SWAP16(0x0006);
        nbns->data.an.flags = SWAP16(0x0000);
        RedFly.getlocalip(nbns->data.an.addr);
        encode(nbns->data.an.name, devname, 0x00); //0x00 = Workstation
        nbns->data.an.name[32] = 0;
        //send answer
        write(buf, NBNS_PACKETLEN+NBNSA_PACKETLEN);
        return 0xFF;
      }
    }
  }

  return 0;
}


//-------------------- Private --------------------


uint8_t RedFlyNBNS::decode(char *dst, char *src)
{
  uint8_t i, j;
  char c;

  for(i=0, j=0; i<15; i++)
  {
    c  = (src[j++]-'A')<<4;
    c |= (src[j++]-'A')<<0;
    if(c == ' ')
    {
      break;
    }
    dst[i] = toupper(c);
  }
  dst[i] = 0;

  return (((src[30]-'A')<<4)|(src[31]-'A')); //0x00 = Workstation
}


void RedFlyNBNS::encode(char *dst, char *src, uint8_t type)
{
  uint8_t i, j;
  char c;

  //encode name
  for(i=0, j=0; (i<15) && src[i]; i++)
  {
    c = toupper(src[i]);
    dst[j++] = 'A'+((c>>4)&0x0f);
    dst[j++] = 'A'+((c>>0)&0x0f);
  }

  //add spaces
  for(; i<15; i++)
  {
    dst[j++] = 'A'+((' '>>4)&0x0f);
    dst[j++] = 'A'+((' '>>0)&0x0f);
  }

  //set type (0x00 = Workstation)
  dst[j++] = 'A'+((type>>4)&0x0f);
  dst[j++] = 'A'+((type>>0)&0x0f);

  return;
}
