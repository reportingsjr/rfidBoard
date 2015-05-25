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

static thread_t *messageThread;

static mailbox_t cr95hfMailbox;
// 10 messages should be enough of a buffer
static msg_t cr95hfMailboxBuf[10];

static uint8_t rxbuf[255];
static uint8_t txbuf[255];

static uint8_t idleCommand[16];

// thread that watches for messages in a mailbox
// when the cr95hf sends a pulse on IRQ_OUT an interrupt is generated
// which reads the message the IC has and puts it in the mailbox.
// This thread loops every x ms and when it sees data parses it and
// calls the appropriate function.
static THD_WORKING_AREA(cr95hfMessageThreadWA, 512);
static THD_FUNCTION(cr95hfMessageThread, arg) {
  (void)arg;
  
  while (!chThdShouldTerminateX()) {
    chEvtWaitAnyTimeout((eventmask_t)1, TIME_INFINITE);
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
}

// Initializes SPI and interrupt for the cr95hf IC.
// Sends initialize command and waits for the chip to start up.
void cr95hf_init(struct pin *IRQ_IN_temp,
                 struct pin *IRQ_OUT_temp,
                 ioportid_t spi_port,
                 uint16_t spi_select_pin) {
  memcpy(&IRQ_IN, IRQ_IN_temp, sizeof(IRQ_IN));
  memcpy(&IRQ_OUT, IRQ_OUT_temp, sizeof(IRQ_OUT));
  
  // initalize static arrays to all zeros
  memset(rxbuf, 0x00, sizeof(rxbuf));
  memset(rxbuf, 0x00, sizeof(txbuf));
  memset(idleCommand, 0x00, sizeof(idleCommand));

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
  palSetPadMode(GPIOA, 1, PAL_MODE_OUTPUT_PUSHPULL);
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
  uint8_t length  = 0x04; // 2 bytes of data
  uint8_t data[4] = {0x02, 0x00, 0x03, 0x00};
  msg_t message;
  
  spiAcquireBus(&SPID1);
  spiSelect(&SPID1);
  // send control byte for send command
  spiSend(&SPID1, 1, &CR95HF_CMD);
  spiSend(&SPID1, 1, &command);
  spiSend(&SPID1, 1, &length);
  spiSend(&SPID1, 4, &data);
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



// Echo is a special command since it does not require a data length to be sent.
// Sends 0x55 and expects to receive 0x55 back if SPI is working.
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
  msg_t message;
  //////////////////////////////////////////////////////////////////////////
  // Temporary!
  // Remove before completing code!
  //////////////////////////////////////////////////////////////////////////
  uint8_t tempIdle[16] = {0x07, 0x0E, 0x02, 0x21, 0x00,  0x79, 0x01, 0x18, 0x00, 
                      0x01, 0x60, 0x60, 0x40, 0x50, 0x3F, 0x01};

  spiAcquireBus(&SPID1);
  spiSelect(&SPID1);
  spiSend(&SPID1, 1, &CR95HF_CMD);
  spiSend(&SPID1, 16, &tempIdle);//&idleCommand);
  spiUnselect(&SPID1);
  spiReleaseBus(&SPID1);
  chMBFetch(&cr95hfMailbox, &message, TIME_INFINITE);
  if(rxbuf[0] == 0x00) {
    if(rxbuf[1] == 0x01) {
      if(rxbuf[2] == 0x02) {
        // The idle command somehow changes how the IC communicates with tags.
        // So we reset the protocol before trying to talk to the tag again.
        setProtocol();
        topazREQA();
        topazRID();
        topazRALL();
      }
    }
  }
  memset(rxbuf, 0x00, sizeof(rxbuf));
}

// tagCalibrate adjusts the threshold detection values for an antenna.
// It starts off at the maximum settings to verify everything 
// is working correctly.
// It then converges/iterates to a set of threshold values that should work
// well for most environments.
// This can be skipped if good DAC Data values are known for a certain antenna.
void tagCalibrate() {
  // Initial idle command. Has a very short timeout period and DAC Data
  // values are not initialized.
  uint8_t thisdata[16] = {0x07, 0x0E, 0x03, 0x21, 0x00,  0x79, 0x01, 0x18, 0x00, 
                      0x02, 0x60, 0x60, 0x00, 0x00, 0x3F, 0x01};
  msg_t message;
  int i;

  for(i = 0; i < 8; i++) {
    spiAcquireBus(&SPID1);
    spiSelect(&SPID1);
    spiSend(&SPID1, 1, &CR95HF_CMD);
    spiSend(&SPID1, 16, &thisdata);
    spiUnselect(&SPID1);
    spiReleaseBus(&SPID1);
    chMBFetch(&cr95hfMailbox, &message, TIME_INFINITE);
    if(rxbuf[0] == 0x00) {
      if(rxbuf[1] == 0x01) {
        if(rxbuf[2] == 0x02) {
          switch(i) {
            case 0:
              thisdata[13] = 0xFC;
              break;
            case 1:
              //error
              break;
            case 2:
              thisdata[13] += 0x40;
              break;
            case 3:
              thisdata[13] += 0x20;
              break;
            case 4:
              thisdata[13] += 0x10;
              break;
            case 5:
              thisdata[13] += 0x08;
              break;
            case 6:
              thisdata[13] += 0x04;
              break;
            case 7:
              // settings are good. Do nothing.
              break;
          }
        } else if(rxbuf[2] == 0x01) {
          switch(i) {
            case 0:
              //error
              break;
            case 1:
              thisdata[13] -= 0x80;
              break;
            case 2:
              thisdata[13] -= 0x40;
              break;
            case 3:
              thisdata[13] -= 0x20;
              break;
            case 4:
              thisdata[13] -= 0x10;
              break;
            case 5:
              thisdata[13] -= 0x08;
              break;
            case 6:
              thisdata[13] -= 0x04;
              break;
            case 7:
              thisdata[13] -= 0x04;
              break;
          }
        }
      }
    }
    memset(rxbuf, 0x00, sizeof(rxbuf));
  }
  // Now that we know appropriate tag values set the idle command to the final
  // values we want for further operations.
  thisdata[2]   = 0x02;
  thisdata[9]   = 0x20;
  thisdata[12]  = thisdata[13] - 0x08;
  thisdata[13] += 0x08;
  memcpy(idleCommand, thisdata, sizeof(idleCommand));
}

void sendRecv(uint8_t *data, uint8_t dataSize, uint8_t topaz, uint8_t splitFrame, 
              uint8_t crc, uint8_t sigBits) {
  uint8_t length = 0;
  msg_t message;
  
  txbuf[0] = CR95HF_CMD;
  txbuf[1] = 0x04; // SendRecv command
  txbuf[2] = dataSize + 1;
  length += 3;
  for(uint8_t i = 0; i < dataSize; i++) {
    txbuf[3 + i] = *(data + i);
  }
  length += dataSize;
  txbuf[length] = (topaz << 7) | (splitFrame << 6) | (crc << 5) | sigBits;
  length += 1;

  spiAcquireBus(&SPID1);
  spiSelect(&SPID1);
  spiSend(&SPID1, length, &txbuf);
  spiUnselect(&SPID1);
  spiReleaseBus(&SPID1);

  chMBFetch(&cr95hfMailbox, &message, TIME_INFINITE);
  switch(rxbuf[0]) {
    case 0x80:
      // decode data
      //memset(rxbuf, 0x00, sizeof(rxbuf));
      break;
    case 0x90:
      // non integer number of bytes received
      // response to ACK or NACK?
      break;
    case 0x86:
      // communication error
      break;
    case 0x87:
      // frame wait time out or no tag
      break;
    case 0x88:
      // invalid SOF
      break;
    case 0x89:
      // receive buffer overflow
      break;
    case 0x8A:
      // framing error
      break;
    case 0x8B:
      // EGT time out
      break;
    case 0x8C:
      // invalid length
      break;
    case 0x8D:
      // CRC error
      break;
    case 0x8E:
      // reception lost without EOF received
      break;
    default:
      // ruh roh
      break;
  }
  //memset(rxbuf, 0x00, sizeof(rxbuf));
  memset(txbuf, 0x00, sizeof(txbuf));
}


// list of RFID commands:
// REQA = 0x26 (request type a)
// WUPA = 0x52 (wake up type a)
// the commands below need an address operand that is:
//  b0xxxxyyy where x is the block (0 to E) and y is the byte in that block
// they also need a 2 byte CRC
// RID = 0x78 (read ID)
// READ 0x01
// RALL = 0x00 (read all)
// WRITE-E = 0x53 (write with erase)
// WRITE-NE = 0x1A (write with no erase)

void topazREQA() {
  uint8_t data = 0x26; //REQA, topaz send format respectively
  sendRecv(&data, 1, 0, 0, 0, 7);
}

void topazWUPA() {
  uint8_t data = 0x52; //WUPA
  sendRecv(&data, 1, 0, 0, 0, 7);
}

void topazRID() {
  uint8_t data[7] = {0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  sendRecv(data, 7, 1, 0, 1, 8);
}

void topazRALL() {
  uint8_t data[7] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  // read the ID so we get the four UID bits we need
  topazRID();
  data[3] = rxbuf[4];
  data[4] = rxbuf[5];
  data[5] = rxbuf[6];
  data[6] = rxbuf[7];
  sendRecv(data, 7, 1, 0, 1, 8);
}

void topazREAD() {
  //
}

void topazWRITEE() {
  //
}

void topazWRITENE() {
  //
}

void topazAdjustRegisters() {
  msg_t message;

  uint8_t adjustModAndGain[6] = {0x09, 0x04, 0x68, 0x01, 0x01, 0xD1};
  uint8_t adjustTimerW[6] = {0x09, 0x04, 0x3A, 0x00, 0x58, 0x04};

  spiAcquireBus(&SPID1);
  spiSelect(&SPID1);
  spiSend(&SPID1, 1, &CR95HF_CMD);
  spiSend(&SPID1, 6, &adjustTimerW);
  spiUnselect(&SPID1);
  spiReleaseBus(&SPID1);
  chMBFetch(&cr95hfMailbox, &message, TIME_INFINITE);
  if(rxbuf[0] == 0x00) {
    if(rxbuf[1] == 0x00) {
      // success
    }
  }
  memset(rxbuf, 0x00, sizeof(rxbuf));

  spiAcquireBus(&SPID1);
  spiSelect(&SPID1);
  spiSend(&SPID1, 1, &CR95HF_CMD);
  spiSend(&SPID1, 6, &adjustModAndGain);
  spiUnselect(&SPID1);
  spiReleaseBus(&SPID1);
  chMBFetch(&cr95hfMailbox, &message, TIME_INFINITE);
  if(rxbuf[0] == 0x00) {
    if(rxbuf[1] == 0x00) {
      // success
    }
  }
  memset(rxbuf, 0x00, sizeof(rxbuf));

}

extern void cr95hfInterrupt(EXTDriver *extp, expchannel_t channel) {
  (void)extp;
  (void)channel;
  // add a message to the mailbox for cr95hfMessageThread
  chSysLockFromISR();
  chEvtSignalI(messageThread, (eventmask_t)1);
  chSysUnlockFromISR();
}
