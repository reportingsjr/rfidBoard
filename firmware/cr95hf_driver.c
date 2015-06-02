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
// This thread infinitely loops and when it sees data parses it and
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
        sens_req();
        uint8_t nfcid[10];
        if(sdd_req(1, nfcid) == 1) {
          sel_req(1, 1, nfcid);
          if(sdd_req(2, nfcid) == 1) {
            sel_req(2, 1, nfcid);
            sdd_req(3, nfcid);
            sel_req(3, 0, nfcid);
          } else {
            sel_req(2, 0, nfcid);
          }
        } else {
          sel_req(1, 0, nfcid);
        }
        //uint8_t blocks[16];
        //type2Read(0x04, blocks);
        //uint8_t data[4] = {0xDE, 0xAD, 0xBE, 0xEF};
        //type2Write(0x04, data);
        //type2Read(0x04, blocks);
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

// This function takes parameters for ISO 14443 type A protocol only
// data is the NFC command to be sent
// dataSize is length (in bytes) of the NFC command to be sent
// topaz is 0 or 1 based on if topaz format should be used
// splitFrame is 
// crc is 0 or 1 depending on if a CRC needs to be appended
// sigBits is number of signifcant bits in the last byte
// returns uint8_t that is the result code. Full data is copied to returnData
uint8_t sendRecv(uint8_t *data, uint8_t dataSize, uint8_t topaz, uint8_t splitFrame, 
              uint8_t crc, uint8_t sigBits, uint8_t *returnData) {
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
  
  memcpy(returnData, rxbuf, 255);
  memset(rxbuf, 0x00, sizeof(rxbuf));
  memset(txbuf, 0x00, sizeof(txbuf));
  return returnData[0];
  /*switch(rxbuf[0]) {
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
  }*/
}


void ISO14443AAdjustRegisters() {
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

// List of NFC Forum NFC-A commands
// SENS_REQ 0x26 - short frame (REQA)
// ALL_REQ 0x52 - short frame (WUPA)
// SDD_REQ 0x93, 0x95 (anti collision CL1 or CL2)
// SEL_REQ 0x93, 0x95 (select CL1 or CL2) // requires CRC
// SLP_REQ 0x50 (halt) // requires CRC

// NFC forum type 2 commands
// READ    0x30
// WRITE   0xA2

// Sends a sens_req (REQA) to the NFC device
// Checks the return value to see what NFCID1 size the device is
// returns 1, 2, or 3 for single, double, or triple. Returns 0 for other.
uint8_t sens_req() {
  uint8_t data = 0x26; 
  uint8_t returnData[255];
  // send the individual bit. No CRC, etc, but it is a short frame (7 bits)
  sendRecv(&data, 1, 0, 0, 0, 7, returnData);

  // check ATQA response to see what bits 7 and 8 are to determine UID size.

  // check it bits 7 and 8 are 0
  if(~(returnData[2] & 1<<7) && ~(returnData[2] & 1<<6)) { // 00
    // NFCID1 size: single (4 bytes)
    return 1;
  } else if (~(returnData[2] & 1<<7) && (returnData[2] & 1<<6)) { // 01
    // NFCID1 size: double (7 bytes)
    return 2;
  } else if ((returnData[2] & 1<<7) && ~(returnData[2] & 1<<6)) { // 10
    // NFCID1 size: triple (10 bytes)
    return 3;
  } else {
    // RFU, so nothing
    return 0;
  }
}

// Sends an all_req (WUPA) to the NFC device
// Checks the return value to see what NFCID1 size the device is
// returns 1, 2, or 3 for single, double, or triple. Returns 0 for other.
uint8_t all_req() {
  uint8_t data = 0x52; 
  uint8_t returnData[255];
  // send the individual bit. No CRC, etc, but it is a short frame (7 bits)
  sendRecv(&data, 1, 0, 0, 0, 7, returnData);

  // should do error checking here. Make sure the first byte is 0x80
  
  // check ATQA response to see what bits 7 and 8 are to determine UID size.
  // we could also check returnData[3] to see if it is 0x0C which means it is
  // a type 1 device (basically topaz/broadcom)

  // check it bits 7 and 8 are 0
  if(~(returnData[2] & 1<<7) && ~(returnData[2] & 1<<6)) { // 00
    // NFCID1 size: single (4 bytes)
    return 1;
  } else if (~(returnData[2] & 1<<7) && (returnData[2] & 1<<6)) { // 01
    // NFCID1 size: double (7 bytes)
    return 2;
  } else if ((returnData[2] & 1<<7) && ~(returnData[2] & 1<<6)) { // 10
    // NFCID1 size: triple (10 bytes)
    return 3;
  } else {
    // RFU, so nothing
    return 0;
  }
}

// accepts current anti collision cascade level (1, 2, or 3) and
// if applicable parts of the uid. Returns 1 if the cascade tag is present
// which means that another level of sdd_req needs to be sent.
// returns 0 if sdd_req was unsuccessful
// returns 2 if no cascade tag and sdd_req was successful.
// fills out nficid param with the returned 3 or 4 bytes of NFCID1 
uint8_t sdd_req(uint8_t cascadeLevel, uint8_t *nfcid) {
  uint8_t returnData[255];
  uint8_t data[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
  uint8_t dataSize = 0;

  // TODO: make these so they can send parts of the nfcid along with them.
  //       this would help if there ever is a collision of devices.
  switch(cascadeLevel) {
    case 1:
      data[0] = 0x93;
      data[1] = 0x20;
      dataSize = 2;
      break;
    case 2:
      data[0] = 0x95;
      data[1] = 0x20;
      dataSize = 2;
      break;
    case 3:
      data[0] = 0x97;
      data[1] = 0x20;
      dataSize = 2;
      break;
    default:
      //return
      break;
  }
  
  sendRecv(data, dataSize, 0, 0, 0, 8, returnData);
  // cr95hf error
  if(returnData[0] != 0x80) {
    return 0;
  }
  // cascade tag, only 3 bytes returned
  if(returnData[2] == 0x88) {
    switch(cascadeLevel) {
      case 1:
        nfcid[0] = returnData[3];
        nfcid[1] = returnData[4];
        nfcid[2] = returnData[5];
        break;
      case 2:
        nfcid[3] = returnData[3];
        nfcid[4] = returnData[4];
        nfcid[5] = returnData[5];
        break;
    }
    return 1;
  } else {
    switch(cascadeLevel) {
      case 1:
        nfcid[0] = returnData[2];
        nfcid[1] = returnData[3];
        nfcid[2] = returnData[4];
        nfcid[3] = returnData[5];
        break;
      case 2:
        nfcid[3] = returnData[2];
        nfcid[4] = returnData[3];
        nfcid[5] = returnData[4];
        nfcid[6] = returnData[5];
        break;
      case 3:
        nfcid[6] = returnData[2];
        nfcid[7] = returnData[3];
        nfcid[8] = returnData[4];
        nfcid[9] = returnData[5];
    }
    return 2;
  }
}

// returns 0 for error
// returns 1 for NFCID1 not complete so we need another cascade level
// returns 2 for NFC-DEP support, probably a phone
// returns 3 for type 2 tag
uint8_t sel_req(uint8_t cascadeLevel, uint8_t cascadeTag, uint8_t *nfcid) {
  uint8_t returnData[255];
  uint8_t data[7];

  switch(cascadeLevel) {
    case 1:
      data[0] = 0x93;
      data[1] = 0x70;
      if(cascadeTag == 0) {
        data[2] = nfcid[0];
        data[3] = nfcid[1];
        data[4] = nfcid[2];
        data[5] = nfcid[3];
      } else {
        data[2] = 0x88;
        data[3] = nfcid[0];
        data[4] = nfcid[1];
        data[5] = nfcid[2];
      }
      data[6] = data[2] ^ data[3] ^ data[4] ^ data[5];
      break;
    case 2:
      data[0] = 0x95;
      data[1] = 0x70;
      if(cascadeTag == 0) {
        data[2] = nfcid[3];
        data[3] = nfcid[4];
        data[4] = nfcid[5];
        data[5] = nfcid[6];
      } else {
        data[2] = 0x88;
        data[3] = nfcid[3];
        data[4] = nfcid[4];
        data[5] = nfcid[5];
      }
      data[6] = data[2] ^ data[3] ^ data[4] ^ data[5];
      break;
    case 3:
      data[0] = 0x97;
      data[1] = 0x70;
      data[2] = nfcid[6];
      data[3] = nfcid[7];
      data[4] = nfcid[8];
      data[5] = nfcid[9];
      data[6] = data[2] ^ data[3] ^ data[4] ^ data[5];
      break;
    default:
      break;
  }

  sendRecv(data, 7, 0, 0, 1, 8, returnData);

  if(returnData[0] != 0x80) {
    // return that it failed
    return 0;
  }
  if(returnData[2] & 1<<2) {
    // NFCID1 not complete, on to the next cascade level!
    return 1;
  }
  if(returnData[2] & 1<<5) {
    // supports NFC-DEP protocol, probably a phone
    type4aRATS();
    return 2;
  }
  if(~(returnData[2] & 1<<5) && ~(returnData[2] & 1<<6)) {
    // type 2 tag
    uint8_t blocks[16];
    type2Read(0x04, blocks);
    return 3;
  }
  // if we made it here it is a type 4a tag which is currently unsupported
  return 0;
}

void slp_req() {
  //
}

// type 2 tag read
// block is the starting block to read
// response contains the 16 bytes (4 blocks) that were read if successful
void type2Read(uint8_t block, uint8_t *response) {
  uint8_t returnData[255];
  uint8_t data[2];
  
  data[0] = 0x30; // read command
  data[1] = block; // block number

  sendRecv(data, 2, 0, 0, 1, 8, returnData);

  if(returnData[0] != 0x80) {
    // error
  }
  if(returnData[1] == 0x04 && (returnData[2] == 0x00 ||
     returnData[2] == 0x01 || returnData[2] == 0x04 ||
     returnData[2] == 0x05)) {
    // NACK sent back, treat as error)
  }
  // copy over the 16 response bytes starting from returnData[2]
  memcpy(response, returnData + 2, 16);
  // return 16 bytes that represent the 4 blocks that were read
}

// type 2 tag write
// block is the block to be written
// writeData is the data to be written and must be 4 bytes
void type2Write(uint8_t block, uint8_t *writeData) {
  uint8_t returnData[255];
  uint8_t data[6];
  data[0] = 0xA2;
  data[1] = block;
  memcpy(data + 2, writeData, 4);

  sendRecv(data, 6, 0, 0, 1, 8, returnData);
}

void type4aRATS() {
  uint8_t data[2] = {0xE0, 0x70}; // RATS with accepted frame size of 128 bytes
  uint8_t returnData[255];

  sendRecv(data, 2, 0, 0, 1, 8, returnData);
  
  if(returnData[0] != 0x80) {
    // error
  }
  if((returnData[3] & 1<<4) &&(returnData[3] & 1<<5) &&(returnData[3] & 1<<6)) {
    // TA(1), TB(1), and TC(1) are all included in this
    // we should do verification here, but that will come later
  }
}

extern void cr95hfInterrupt(EXTDriver *extp, expchannel_t channel) {
  (void)extp;
  (void)channel;
  // add a message to the mailbox for cr95hfMessageThread
  chSysLockFromISR();
  chEvtSignalI(messageThread, (eventmask_t)1);
  chSysUnlockFromISR();
}
