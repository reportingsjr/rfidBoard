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
void topazAdjustRegisters(void);
uint8_t sendRecv(uint8_t *, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t *);
void topazREQA(void);
void topazWUPA(void);
uint8_t topazRID(uint8_t *);
void topazRALL(void);
void topazREAD(void);
void topazWRITEE(void);
void topazWRITENE(void);
void sens_req(void);
void all_req(void);
void sdd_req(void);
void sel_req(void);
void slp_req(void);
void read(void);
void write(void);
extern void cr95hfInterrupt(EXTDriver *extp, expchannel_t channel);

