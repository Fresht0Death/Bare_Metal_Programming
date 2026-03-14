/*
 * tim.c
 *
 *  Created on: Mar 13, 2026
 *      Author: Freshmai
 */


#include "stm32f446xx.h"


#define TM2CR1EN	(1U<<0)
#define APB1TIM2EN	(1U<<0)



void tim2_startTimer(int buttonPressed){

	if(buttonPressed == 1){
	/* Enable timer */
	TIM2->CR1 |= TM2CR1EN;

	}
	else{return;}





}




void tim2_1hz_init(void)
{

	/* Enable clock access to tim2 */
		RCC->APB1ENR |= APB1TIM2EN;


		/* Set prescale value */

		TIM2->PSC = 15999 - 1; // 16 000 000 000 / 16000 = 1000 Hz = 1 kHz



		/* Set auto reload value */
		// OG : 10000 - 1

		TIM2->ARR = 10000 - 1; // 10 000 / 1000 = 1hz


		/* Clear counter */
		TIM2->CNT = 0;


}

