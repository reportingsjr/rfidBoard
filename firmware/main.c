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
#include "halconf.h"
#include "cr95hf_driver.h"

static void readReadycb(EXTDriver *extp, expchannel_t channel);

static const SPIConfig spicfg = {
  NULL,
  GPIOA,
  GPIOA_SPI1NSS,
  SPI_CR1_BR_2
};


static THD_WORKING_AREA(ledBlinkerThreadWA, 128);
static msg_t ledBlinkerThread(void *arg) {
  (void)arg;
  while (TRUE) {
    echo();
    osalSysPolledDelayX(OSAL_MS2ST(500));
  }

  return (msg_t) 0;
}



static void readReadycb(EXTDriver *extp, expchannel_t channel) {                
  (void)extp;                                                                   
  (void)channel;                                                                
  palClearPad(GPIOA, 3);                                                        
  osalSysPolledDelayX(OSAL_US2ST(20));
  palSetPad(GPIOA, 3);                                                          
} 

static const EXTConfig extcfg = {                                               
  {                                                                             
    {EXT_CH_MODE_DISABLED, NULL},  
    {EXT_CH_MODE_DISABLED, NULL},                                               
    {EXT_CH_MODE_FALLING_EDGE | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOA, readReadycb},                                               
    {EXT_CH_MODE_DISABLED, NULL},                                               
    {EXT_CH_MODE_DISABLED, NULL},                                               
    {EXT_CH_MODE_DISABLED, NULL},                                               
    {EXT_CH_MODE_DISABLED, NULL},                                               
    {EXT_CH_MODE_DISABLED, NULL},                                               
    {EXT_CH_MODE_DISABLED, NULL},                                               
    {EXT_CH_MODE_DISABLED, NULL},                                               
    {EXT_CH_MODE_DISABLED, NULL},                                               
    {EXT_CH_MODE_DISABLED, NULL},                                               
    {EXT_CH_MODE_DISABLED, NULL }, 
    {EXT_CH_MODE_DISABLED, NULL},                                               
    {EXT_CH_MODE_DISABLED, NULL},                                               
    {EXT_CH_MODE_DISABLED, NULL}                                                
  }                                                                             
};

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

  extStart(&EXTD1, &extcfg);

  spiStart(&SPID1, &spicfg);

  palSetPadMode(GPIOA, 2, PAL_MODE_INPUT);
  palSetPadMode(GPIOA, 3, PAL_MODE_OUTPUT_PUSHPULL);
  // Send a 20us pulse to wake up the CR95HF
  palClearPad(GPIOA, 3);
  // delay for 20 microseconds
  osalSysPolledDelayX(OSAL_US2ST(20));
  palSetPad(GPIOA, 3);
  // wait 10 ms to let the CR95HF set itself up
  osalSysPolledDelayX(OSAL_MS2ST(10));
  setProtocol();
  rfidREQA();
  /*
   * Creates the example thread.
   */
  chThdCreateStatic(ledBlinkerThreadWA, sizeof(ledBlinkerThreadWA), HIGHPRIO, ledBlinkerThread, NULL);
  return 0;
}