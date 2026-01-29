/*
 * tim.c
 *
 *  Created on: Jan 29, 2026
 *      Author: Freshmai
 */

// boards header file
#include "stm32f4xx.h"




// symbolic names:
#define TIM3_ENR				(1U<<1) /* Tim3 enable clock access bit */
#define TIM3_CR1EN 				(1U<<0) /* Tim3 CR1 enable timer bit */





void tim3_10hz_init/* name of init function or tim2 and 10hz  */(void)
{


	/* Enable clock access to tim3 */
		/* searh for APB1 enable register to see what bit needs to be 1 to enable
		 * clock access to TIM3
		 * then enable clock access with the symbolic name */
	RCC->APB1ENR |= TIM3_ENR;

	/* FOR HOW TO SOLVE FOR PSC AND ARR
	 * When you come back later, you should be able to fill blanks by asking:
   * What is fTIM for TIM3? (APB1 timer clock)
   * What tick rate do I want after PSC? (pick 1kHz/10kHz/1MHz)
   * Compute PSC: PSC = (fTIM / tick) - 1
   * Compute ARR: ARR = (tick / desired_update) - 1  */



	/* Set prescale value ^^^^^
	 * put into prescaler register
	 * reduce clock to 10hz */
	TIM3->PSC = (45000000/10000) - 1;

	/* Set auto reload value/register  ^^^^^^^
	 * by putting auto reaoad register to 10hz */
	TIM3->ARR = (10000/1) - 1;

	/* Clear counter */
	TIM3->CNT = 0;

	/* Enable timer
	 * find particular bit inside the Timer control register
	 * this is found in our reference manual
	 * TIMx_CR1
	 * use symbolic name to set this */
	TIM3->CR1 |= TIM3_CR1EN;



}








