/*
 * button.c
 *
 *  Created on: Mar 13, 2026
 *      Author: Freshmai
 */


#include "stm32f446xx.h"


#define GPIOAEN			(1U<<0)
#define PA0_INPUT0		(1U<<0)
#define PA0_INPUT1		(1U<<1)
#define PA0_IDR			(1U<<0)


void pa0_input(void)
{
	// enable clock for GPIOA
	RCC->AHB1ENR |= GPIOAEN;


	// set pa1 as analog: 01
	GPIOA->MODER &=~ PA0_INPUT0;
	GPIOA->MODER &=~ PA0_INPUT1;



}


int pa0_read(void){

	if(GPIOA->IDR & PA0_IDR){return 1;}

	else{return 0;}






}

