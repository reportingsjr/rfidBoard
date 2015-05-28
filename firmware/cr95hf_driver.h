// STM32 CR95HF chibios driver
#include "stdint.h"
#include "hal.h"

struct pin {
  ioportid_t port;
  uint16_t pin;
};

void cr95hf_init(struct pin *IRQ_IN, struct pin *IRQ_OUT, ioportid_t, uint16_t);
void echo(void);
void setProtocol(void);
void idle(void);
void tagCalibrate(void);
void typeAAdjustRegisters(void);
uint8_t sendRecv(uint8_t *, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t *);
/*void topazREQA(void);
void topazWUPA(void);
uint8_t topazRID(uint8_t *);
void topazRALL(void);
void topazREAD(void);
void topazWRITEE(void);
void topazWRITENE(void);*/
uint8_t sens_req(void);
uint8_t all_req(void);
uint8_t sdd_req(uint8_t, uint8_t *);
uint8_t sel_req(uint8_t, uint8_t, uint8_t *);
void slp_req(void);
void read(void);
void write(void);
void rats(void);
extern void cr95hfInterrupt(EXTDriver *extp, expchannel_t channel);

