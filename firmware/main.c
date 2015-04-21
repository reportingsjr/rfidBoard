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

static const EXTConfig extcfg = {
  {
    {EXT_CH_MODE_DISABLED, NULL},  
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_FALLING_EDGE | EXT_MODE_GPIOA, 
     cr95hfInterrupt},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL}, 
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

  struct pin IRQ_OUT = {GPIOA, 2};
  struct pin IRQ_IN = {GPIOA, 3};
  
  extStart(&EXTD1, &extcfg);
  cr95hf_init(&IRQ_IN, &IRQ_OUT, GPIOA, GPIOA_SPI1NSS);
  extChannelEnable(&EXTD1, (expchannel_t) 2);
  
  echo();
  setProtocol();
  idle();
  chThdSleep(TIME_INFINITE);
  //setProtocol();
  //rfidREQA();
  /*
   * Creates the example thread.
   */
  return 0;
}
