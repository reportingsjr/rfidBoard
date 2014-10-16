//=======================================================================================
// STM32 AntiLib Project
// Module : GPIO
// Description : Macros for configure GPIO's
// Author : Radoslaw Kwiecien
// e-mail : radek@dxp.pl
// website : http://en.radzio.dxp.pl
//=======================================================================================
#ifndef ANTILIB_GPIO_H
#define ANTILIB_GPIO_H

	#define GPIO_CNF_INPUT_ANALOG		0
	#define GPIO_CNF_INPUT_FLOATING		1
	#define GPIO_CNF_INPUT_PULLUPDOWN	2

	#define GPIO_CNF_OUTPUT_PUSHPULL	0
	#define GPIO_CNF_OUTPUT_OPENDRAIN	1
	#define GPIO_CNF_AFIO_PUSHPULL		2
	#define GPIO_CNF_AFIO_OPENDRAIN		3

	#define GPIO_MODE_INPUT				0
	#define GPIO_MODE_OUTPUT10MHz		1
	#define GPIO_MODE_OUTPUT2MHz		2
	#define GPIO_MODE_OUTPUT50MHz		3

	#define GPIOCONF(mode, cnf)	((cnf << 2) | (mode))
	#define GPIOPINCONFL(pin, conf) (conf << (pin * 4))
	#define GPIOPINCONFH(pin, conf) (conf << ((pin - 8) * 4))

	#define CONFMASKL(pin) ((u32)~(15 << (pin * 4)))
	#define CONFMASKH(pin) ((u32)~(15 << ((pin - 8) * 4)))

#endif
//=======================================================================================
//
//=======================================================================================