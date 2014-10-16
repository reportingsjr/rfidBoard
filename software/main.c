#include "stm32f10x.h"
#include "antilib_gpio.h"

int main(void) {
  volatile int delay;

  // Enable the clock for port C gpio
  RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
  // Configure port C, pin 8 as a push pull output
  GPIOC->CRH = (GPIOC->CRH & CONFMASKH(8)) | GPIOPINCONFH(8, GPIOCONF(GPIO_MODE_OUTPUT2MHz, GPIO_CNF_OUTPUT_PUSHPULL));
  for(;;){
    // Set the LED as on for 500k cycles
    for(delay = 0; delay < 500000; delay++) {
      GPIOC->BSRR = (1 << 8);
    }
    // Set the LED as off for 500k cycles
    for(delay = 0; delay < 500000; delay++) {
      GPIOC->BRR = (1 << 8);
    }
  }
}
