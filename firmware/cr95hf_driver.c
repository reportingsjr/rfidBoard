// STM CR95HF chibios driver
#include "cr95hf_driver.h"
#include "ch.h"
#include "hal.h"
#include "string.h"

uint8_t CR95HF_CMD = 0x00;
uint8_t CR95HF_POLL = 0x03;
uint8_t CR95HF_READ = 0x02;
uint8_t CR95HF_RESET = 0x01;

static struct pin IRQ_IN, IRQ_OUT;
static SPIConfig spicfg;

// Initializes SPI and interrupt for the cr95hf IC.
// Sends initialize command and waits for the chip to start up.
void cr95hf_init(struct pin *IRQ_IN_temp,
                 struct pin *IRQ_OUT_temp,
                 ioportid_t spi_port,
                 uint16_t spi_select_pin) {
  memcpy(&IRQ_IN, IRQ_IN_temp, sizeof(IRQ_IN));
  memcpy(&IRQ_OUT, IRQ_OUT_temp, sizeof(IRQ_OUT));
  
  spicfg = (SPIConfig) {
    NULL,
    spi_port,
    spi_select_pin,
    SPI_CR1_BR_2
  };
  spiStart(&SPID1, &spicfg);
  
  // send idle command to start from known state
  // send wake up on IRQ_IN pin
  palSetPadMode(IRQ_OUT.port, IRQ_OUT.pin, PAL_MODE_INPUT);
  palSetPadMode(IRQ_IN.port, IRQ_IN.pin, PAL_MODE_OUTPUT_PUSHPULL);
  // Send a 20us pulse to wake up the CR95HF
  palClearPad(IRQ_IN.port, IRQ_IN.pin);
  // delay for 20 microseconds so the cr95hf sees it for sure
  // (this is double the minimum)
  chSysPolledDelayX(US2RTC(STM32_HCLK, 20));
  palSetPad(IRQ_IN.port, IRQ_IN.pin);
  // wait 10 ms to let the CR95HF set itself up
  chSysPolledDelayX(MS2RTC(STM32_HCLK, 10));
}

void setProtocol() {
  uint8_t command = 0x02; // protocol select
  uint8_t length  = 0x02; // 2 bytes of data
  uint8_t data[2] = {0x02, 0x00};
  static uint8_t rxbuf[2];
  
  spiSelect(&SPID1);
  // send control byte for send command
  spiSend(&SPID1, 1, &CR95HF_CMD);
  spiSend(&SPID1, 1, &command);
  spiSend(&SPID1, 1, &length);
  spiSend(&SPID1, 2, &data);
  spiUnselect(&SPID1);

  // Loop until IRQ_OUT is low which means the data is ready.
  while(palReadPad(GPIOA, 2) != PAL_LOW) {
    chSysPolledDelayX(US2RTC(STM32_HCLK, 10));
  }
  spiSelect(&SPID1);
  spiSend(&SPID1, 1, &CR95HF_READ);
  spiReceive(&SPID1, 2, &rxbuf);
  spiUnselect(&SPID1);
}

void rfidREQA() {
  uint8_t sendRecv = 0x04;
  uint8_t length = 0x02;
  uint8_t data[2] = {0x26, 0x07}; //REQA, topaz send format respectively

  uint8_t resultCode = 0x00;
  uint8_t resultLength = 0x00;
  uint8_t resultData[255];
  
  spiSelect(&SPID1);
  // send command byte
  spiSend(&SPID1, 1, &CR95HF_CMD);
  spiSend(&SPID1, 1, &sendRecv);
  spiSend(&SPID1, 1, &length);
  spiSend(&SPID1, 2, &data);
  spiUnselect(&SPID1);

  // Loop until IRQ_OUT is low which means the data is ready.
  while(palReadPad(GPIOA, 2) != PAL_LOW) {
    chSysPolledDelayX(US2RTC(STM32_HCLK, 10));
  }
  spiSelect(&SPID1);
  spiSend(&SPID1, 1, &CR95HF_READ);
  spiReceive(&SPID1, 1, &resultCode);
  spiReceive(&SPID1, 1, &resultLength);
  spiReceive(&SPID1, resultLength, &resultData);
  spiUnselect(&SPID1);
}

void echo() {
  uint8_t echo = 0x55;
  static uint8_t rxbuf[2];
  
  spiSelect(&SPID1);
  spiSend(&SPID1, 1, &CR95HF_CMD);
  spiSend(&SPID1, 1, &echo);
  spiUnselect(&SPID1);
  
  chSysPolledDelayX(US2RTC(STM32_HCLK, 10));
  spiSelect(&SPID1);
  // Loop until IRQ_OUT is low which means the data is ready.
  while(palReadPad(IRQ_OUT.port, IRQ_OUT.pin) != PAL_LOW) {
  }
  spiUnselect(&SPID1);
  spiSelect(&SPID1);
  spiSend(&SPID1, 1, &CR95HF_READ);
  spiReceive(&SPID1, 1, &rxbuf);
  spiUnselect(&SPID1);
}

// thread that watches for messages in a mailbox
// when the cr95hf sends a pulse on IRQ_OUT an interrupt is generated
// which reads the message the IC has and puts it in the mailbox.
// This thread loops every x ms and when it sees data parses it and
// calls the appropriate function.
msg_t watchForMessage(void *arg) {
  (void)arg;
  
  while (TRUE) {
    // see if there are message(s) in the mailbox
    // if there are parse the message(s)
    // if not go back to sleep for x ms.
    chThdSleepMilliseconds(10);
  }

  return (msg_t) 0;
}
