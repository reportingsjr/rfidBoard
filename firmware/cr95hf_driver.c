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

static THD_WORKING_AREA(cr95hfMessageThreadWA, 512);
static thread_t *messageThread;

static mailbox_t cr95hfMailbox;
// 10 messages should be enough of a buffer
static msg_t cr95hfMailboxBuf[10];

static uint8_t rxbuf[255];

// Initializes SPI and interrupt for the cr95hf IC.
// Sends initialize command and waits for the chip to start up.
void cr95hf_init(struct pin *IRQ_IN_temp,
                 struct pin *IRQ_OUT_temp,
                 ioportid_t spi_port,
                 uint16_t spi_select_pin) {
  memcpy(&IRQ_IN, IRQ_IN_temp, sizeof(IRQ_IN));
  memcpy(&IRQ_OUT, IRQ_OUT_temp, sizeof(IRQ_OUT));
  
  memset(rxbuf, 0x00, sizeof(rxbuf));

  chMBObjectInit(&cr95hfMailbox, cr95hfMailboxBuf, sizeof(cr95hfMailboxBuf)/sizeof(msg_t));

  spicfg = (SPIConfig) {
    NULL,
    spi_port,
    spi_select_pin,
    SPI_CR1_BR_2
  };
  spiStart(&SPID1, &spicfg);
  // send a reset command just in case the cr95hf hasn't been powered off
  spiSelect(&SPID1);
  spiSend(&SPID1, 1, &CR95HF_RESET);
  spiUnselect(&SPID1);

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
  
  //start the thread that watches for messages from the cr95hf
  messageThread = chThdCreateStatic(cr95hfMessageThreadWA, 
                                    sizeof(cr95hfMessageThreadWA), 
                                    NORMALPRIO, cr95hfMessageThread, NULL);
}

void setProtocol() {
  uint8_t command = 0x02; // protocol select
  uint8_t length  = 0x02; // 2 bytes of data
  uint8_t data[2] = {0x02, 0x00};
  msg_t message;
  
  spiAcquireBus(&SPID1);
  spiSelect(&SPID1);
  // send control byte for send command
  spiSend(&SPID1, 1, &CR95HF_CMD);
  spiSend(&SPID1, 1, &command);
  spiSend(&SPID1, 1, &length);
  spiSend(&SPID1, 2, &data);
  spiUnselect(&SPID1);
  spiReleaseBus(&SPID1);
  chMBFetch(&cr95hfMailbox, &message, TIME_INFINITE);
  if(rxbuf[0] == 0x00) {
    // everything went as planned
  } else if(rxbuf[0] == 0x82) {
    // invalid command length
  }
  memset(rxbuf, 0x00, sizeof(rxbuf));
}

void rfidREQA() {
  uint8_t sendRecv = 0x04;
  uint8_t length = 0x02;
  uint8_t data[2] = {0x26, 0x07}; //REQA, topaz send format respectively

  spiSelect(&SPID1);
  // send command byte
  spiSend(&SPID1, 1, &CR95HF_CMD);
  spiSend(&SPID1, 1, &sendRecv);
  spiSend(&SPID1, 1, &length);
  spiSend(&SPID1, 2, &data);
  spiUnselect(&SPID1);
}

void echo() {
  uint8_t echo = 0x55;
  msg_t message;
  
  spiAcquireBus(&SPID1);
  spiSelect(&SPID1);
  spiSend(&SPID1, 1, &CR95HF_CMD);
  spiSend(&SPID1, 1, &echo);
  spiUnselect(&SPID1);
  // watch for a message here and when received parse the data
  spiReleaseBus(&SPID1);
  chMBFetch(&cr95hfMailbox, &message, TIME_INFINITE);
  if(rxbuf[0] == (msg_t)0x55) {
    // echo was a success, end function now
  } else {
    // throw an error here
  }
  memset(rxbuf, 0x00, sizeof(rxbuf));
}

void idle() {
  uint8_t data[16] = {0x07, 0x0E, 0x0A, 0x21, 0x00,  0x79, 0x01, 0x18, 0x00, 
                      0x20, 0x60, 0x60, 0x64, 0x74, 0x3F, 0x08};
  msg_t message;

  spiAcquireBus(&SPID1);
  spiSelect(&SPID1);
  spiSend(&SPID1, 1 ,&CR95HF_CMD);
  spiSend(&SPID1, 16, &data);
  spiUnselect(&SPID1);
  spiReleaseBus(&SPID1);
  chMBFetch(&cr95hfMailbox, &message, TIME_INFINITE);
  if(rxbuf[0] == 0x00) {
    if(rxbuf[1] == 0x01) {
      if(rxbuf[2] == 0x02) {
        memset(rxbuf, 0x00, sizeof(rxbuf));
      }
    }
  }
  memset(rxbuf, 0x00, sizeof(rxbuf));
}

// thread that watches for messages in a mailbox
// when the cr95hf sends a pulse on IRQ_OUT an interrupt is generated
// which reads the message the IC has and puts it in the mailbox.
// This thread loops every x ms and when it sees data parses it and
// calls the appropriate function.
msg_t cr95hfMessageThread(void *arg) {
  (void)arg;
  
  while (!chThdShouldTerminateX()) {
    chEvtWaitAny((eventmask_t)1);
    spiAcquireBus(&SPID1);
    spiSelect(&SPID1);
    spiSend(&SPID1, 1, &CR95HF_READ);
    // get the response code
    spiReceive(&SPID1, sizeof(rxbuf), &rxbuf);
    spiUnselect(&SPID1);
    spiReleaseBus(&SPID1);
    chMBPost(&cr95hfMailbox, (msg_t)0x00, TIME_INFINITE);
    // clear variables before next loop
  }

  return (msg_t) 0;
}

extern void cr95hfInterrupt(EXTDriver *extp, expchannel_t channel) {
  (void)extp;
  (void)channel;
  // add a message to the mailbox for cr95hfMessageThread
  chSysLockFromISR();
  chEvtSignalI(messageThread, (eventmask_t)1);
  chSysUnlockFromISR();
}
