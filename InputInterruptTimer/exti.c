/*
 * exti.c
 *
 *  Created on: Feb 12, 2026
 *      Author: Freshmai
 */


#include "exti.h"
#include "stm32f4xx.h"

#define GPIOCEN       (1U<<2)// what bit must be enabled for GPIOC to be enabled
#define SYSCFGEN      (1U<<14)// what bit must be enabled to enable system configuration


void pc13_exti_init(void)
{


	/* Best Practice: Disable global interupt   */
	__disable_irq();


	/* Enable clock access for GPIOC */
	RCC->AHB1ENR |= GPIOCEN;

	/* Best practice: set PC13 as input */
		// check mode register in ref manual
		// we look for MODERx and see what bits
		// correspond to pc13 and look at truth
		// table for how to config as input mode
	GPIOC->MODER &=~ (1U<<26);
	GPIOC->MODER &=~ (1U<<27);



	/* Enable clock access to SYSCFG */
		// what bus is SYSCFG connected to?
		// go to BUS name enable register to check
		// check which bit enable clock access to SYSCFG
	RCC->APB2ENR |= SYSCFGEN;

	/* Select PORTC for EXTI13 */
		// go to SYSCFG exti control register
		// note the seperation and the truth table
		// look for EXTI13 in the xth register which holds this
		// then set the bit in order to connect to PAC[x] based on the truth table
	SYSCFG->EXTICR[3] |= (1U<<5);  // simiarly to our alt-func register we use an array to access the nth EXTICRn by using n-1 based indexing




	/* Unmask/Uncover EXTI13 */
		// go to interrupt mask register(EXTI_IMR)
		// we are interested in line 13 so we look for
		// the which corresponds to this
		// look at the truth table about how to unmask it
	EXTI->IMR |= (1U<<13);


	/* Select falling edge trigger */
		// go to falling trigger selection register for EXTI
		// look at the truth table to enable falling trigger
		// find the correspinding bit which fits for 13
	EXTI->FTSR |= (1U<<13);

	/* Enable exti line in NVIC */
		// use a function that comes in our stm32f4xx.h file
	NVIC_EnableIRQ(EXTI15_10_IRQn);


	/* Enable global interrupts */
	__enable_irq();



}
