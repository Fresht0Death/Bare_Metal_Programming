/*
 * led.c
 *
 *  Created on: Mar 13, 2026
 *      Author: Freshmai
 */


#include "stm32f446xx.h"


#define GPIOAEN             (1U<<0)
#define PA1OUT_2			(1U<<2)
#define PA1OUT_3			(1U<<3)
#define PA1_PSH_PLL			(1U<<1)
#define PA1_MED_2           (1U<<1)
#define PA1_MED_3			(1U<<1)
#define PA1_BSS				(1U<<1)
#define PA1_BSR				(1U<<17)




void pa1_output(void){

	// enable clock for GPIOA
	RCC->AHB1ENR |= GPIOAEN;


	// set pa1 as analog: 01
	GPIOA->MODER &=~ PA1OUT_3;
	GPIOA->MODER |= PA1OUT_2;

	// setting output type as push-pull : 0
	GPIOA->OTYPER &=~ PA1_PSH_PLL;

	// set output speed: 01 = Medium
	GPIOA->OSPEEDR &=~ PA1_MED_3;
	GPIOA->OSPEEDR |= PA1_MED_2;

}



void led_on(void){


	GPIOA->BSRR |= PA1_BSS;

}

void led_off(void){


	GPIOA->BSRR |= PA1_BSR;

}
