/*
    ChibiOS/RT - Copyright (C) 2006-2013 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "ch.h"
#include "hal.h"
#include "test.h"

static void echo(void);
static void setProtocol(void);
static void rfidREQA(void);


static const SPIConfig spicfg = {
  NULL,
  GPIOA,
  GPIOA_SPI1NSS,
  SPI_CR1_BR_2
};



static WORKING_AREA(ledBlinkerThreadWA, 128);
static msg_t ledBlinkerThread(void *arg) {
  (void)arg;
  while (TRUE) {
    echo();
    halPolledDelay(MS2RTT(500));
  }

  return (msg_t) 0;
}

static void setProtocol() {
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
    halPolledDelay(US2RTT(10));                                                   
  }                                                                             
  spiSelect(&SPID1);                                                            
  spiSend(&SPID1, 1, &read);                                                    
  spiReceive(&SPID1, 2, &rxbuf);                                               
  spiUnselect(&SPID1);
}

static void rfidREQA() {
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
    halPolledDelay(US2RTT(10));                                                 
  }                                                                             
  spiSelect(&SPID1);                                                            
  spiSend(&SPID1, 1, &read);                                                    
  spiReceive(&SPID1, 1, &resultCode);
  spiReceive(&SPID1, 1, &resultLength);
  spiReceive(&SPID1, resultLength, &resultData);
  spiUnselect(&SPID1);
}

static void echo() {
  uint8_t echo = 0x55;
  uint8_t control = 0x00;
  uint8_t poll = 0x03;
  uint8_t read = 0x02;
  static uint8_t rxbuf[20];
  
  spiSelect(&SPID1);
  spiSend(&SPID1, 1, &control);
  spiSend(&SPID1, 1, &echo);
  spiUnselect(&SPID1);

  halPolledDelay(US2RTT(10));
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

/*
 * Application entry point.
 */
int main(void) {

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();

  EXTD1

  spiStart(&SPID1, &spicfg);

  palSetPadMode(GPIOA, 2, PAL_MODE_INPUT);
  palSetPadMode(GPIOA, 3, PAL_MODE_OUTPUT_PUSHPULL);
  // Send a 20us pulse to wake up the CR95HF
  palClearPad(GPIOA, 3);
  // delay for 20 microseconds
  halPolledDelay(US2RTT(20));
  palSetPad(GPIOA, 3);
  // wait 10 ms to let the CR95HF set itself up
  chThdSleepMilliseconds(15);
  setProtocol();
  rfidREQA();
  /*
   * Creates the example thread.
   */
  chThdCreateStatic(ledBlinkerThreadWA, sizeof(ledBlinkerThreadWA), HIGHPRIO, ledBlinkerThread, NULL);
  return 0;
}
