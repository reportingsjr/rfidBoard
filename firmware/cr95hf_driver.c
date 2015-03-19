// STM CR95HF chibios driver
#include "cr95hf_driver.h"
#include "hal.h"

void setProtocol() {
  uint8_t control = 0x00; // send command
  uint8_t command = 0x02; // protocol select
  uint8_t length  = 0x02; // 2 bytes of data
  uint8_t data[2] = {0x02, 0x00};
  uint8_t read = 0x02;                                                          
  static uint8_t rxbuf[2];
  
  spiSelect(&SPID1);
  spiSend(&SPID1, 1, &control);
  spiSend(&SPID1, 1, &command);
  spiSend(&SPID1, 1, &length);
  spiSend(&SPID1, 2, &data);
  spiUnselect(&SPID1);

  // Loop until IRQ_OUT is low which means the data is ready.                   
  while(palReadPad(GPIOA, 2) != PAL_LOW) {
    osalSysPolledDelayX(OSAL_US2ST(10));                                                   
  }                                                                             
  spiSelect(&SPID1);                                                            
  spiSend(&SPID1, 1, &read);                                                    
  spiReceive(&SPID1, 2, &rxbuf);                                               
  spiUnselect(&SPID1);
}

void rfidREQA() {
  uint8_t command = 0x00;
  uint8_t sendRecv = 0x04;
  uint8_t length = 0x02;
  uint8_t data[2] = {0x26, 0x07}; //REQA, topaz send format respectively

  uint8_t read = 0x02;
  uint8_t resultCode = 0x00;
  uint8_t resultLength = 0x00;
  uint8_t resultData[255];
  
  spiSelect(&SPID1);
  spiSend(&SPID1, 1, &command);
  spiSend(&SPID1, 1, &sendRecv);
  spiSend(&SPID1, 1, &length);
  spiSend(&SPID1, 2, &data);
  spiUnselect(&SPID1);

  // Loop until IRQ_OUT is low which means the data is ready.                   
  while(palReadPad(GPIOA, 2) != PAL_LOW) {                                      
    osalSysPolledDelayX(OSAL_US2ST(10));
  }                                                                             
  spiSelect(&SPID1);                                                            
  spiSend(&SPID1, 1, &read);                                                    
  spiReceive(&SPID1, 1, &resultCode);
  spiReceive(&SPID1, 1, &resultLength);
  spiReceive(&SPID1, resultLength, &resultData);
  spiUnselect(&SPID1);
}

void echo() {
  uint8_t echo = 0x55;
  uint8_t control = 0x00;
  uint8_t poll = 0x03;
  uint8_t read = 0x02;
  static uint8_t rxbuf[20];
  
  spiSelect(&SPID1);
  spiSend(&SPID1, 1, &control);
  spiSend(&SPID1, 1, &echo);
  spiUnselect(&SPID1);
  
  osalSysPolledDelayX(OSAL_US2ST(10));
  spiSelect(&SPID1);
  // Loop until IRQ_OUT is low which means the data is ready.
  while(palReadPad(GPIOA, 2) != PAL_LOW) {
    spiSend(&SPID1, 1, &poll);
  }
  spiUnselect(&SPID1);
  spiSelect(&SPID1);
  spiSend(&SPID1, 1, &read);
  spiReceive(&SPID1, 10, &rxbuf);
  spiUnselect(&SPID1);
}
