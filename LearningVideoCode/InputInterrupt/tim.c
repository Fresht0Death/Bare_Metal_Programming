/*
 * tim.c
 *
 *  Created on: Jan 27, 2026
 *      Author: Freshmai
 */


#include "stm32f4xx.h"

#define TIM2EN				(1U<<0)
#define CR1_CEN				(1U<<0)
#define GPIOAEN				(1U<<0)

#define AF6_TIM       (1U<<25)
#define TIM3EN				(1U<<1)
#define CCER_CC1S     (1U<<0)
#define CCER_CC1E     (1U<<0)




void tim2_1hz_init(void)
{
	/* Enable clock access to tim2 */
	RCC->APB1ENR |= TIM2EN;


	/* Set prescale value */
	TIM2->PSC = 1600 - 1; // 16 000 000 000 / 1600 = 10 000


	/* Set auto reload value */
	TIM2->ARR = 10000 - 1; // 10 000 / 10 000 = 1hz

	/* Clear counter */
	TIM2->CNT = 0;

	/* Enable timer */
	TIM2->CR1 |= CR1_CEN;

}

void tim2_output_compare_pa5(void)
{

	/* Enable clock access to GPIOA */
	RCC->AHB1ENR |= GPIOAEN;

	/* Set PA5 to alternate function mode */
		// go to MODER and look for MODER5 and see what must be for alt-func mode
	GPIOA->MODER &=~ (1U<<10);
	GPIOA->MODER |= (1U<<11);

	/* Set PA5 alternate function type to TIM2_CH1(AF01) */
	 // this can be seen in alternate function mapping
	 GPIOA->AFR[0] |= /* what does truth table say for AFRL5 */ (1U<<20);
										// create symbolic name for readbility

	/* Use same code from tim2_1HZ_init() */
	/* Enable clock access to tim2 */
	RCC->APB1ENR |= TIM2EN;


	/* Set prescale value */
	TIM2->PSC = 1600 - 1; // 16 000 000 000 / 1600 = 10 000


	/* Set auto reload value */
	TIM2->ARR = 10000 - 1; // 10 000 / 10 000 = 1hz


	/* Set output compare toggle mode */
	 // go to reference manual and look for TIMx_CCMR1
	 // we are looking for OC1M because we are dealing with channel 1
	 // look for what we have to set it to set it to toggle mode
	 // that is what bits should be set to what????????????????
	 TIM2->CCMR1 = (1U<<4) | (1U<<5); // or use symbolic name for readbility


	/* Enable TIM2 CH1 in compare mode */
	 // look in reference manual for
	 // TIMX_CCER
	 // look for the bit that we have to set to capture/compare enabled
	 TIM2->CCER |= (1U<<0); // or use symbloc name for readability




	/* Clear counter */
	TIM2->CNT = 0;

	/* Enable timer */
	TIM2->CR1 |= CR1_CEN;

}

// capture PA5 speed using Timer 3
void tim3_pa6_input_capture(void)
{
	// Go to block diagram for Alt-function table
	// note: PA6 when we set to AF02 it acts as TIM3_CH1


	/* Enable clock access to GPIOA */
	RCC->AHB1ENR |= GPIOAEN;         // enabling again so we can have function act independently

	/* Set PA6 mode to alternate function */
	GPIOA->MODER &=~ (1U<<12);
	GPIOA->MODER |= (1U<<13);

	/* Set PA6 alternate function type to TIM3_CH1 (AF02) */
		// go to reference manual and look for GPIO altenrate func register for AFRL6
		// this corresponds to bits 24-27
		// check how yo set to alt func mode
		// go to truth table and not we have to set bit 25 to 1
				// use symbolic name
	GPIOA->AFR[0] |= AF6_TIM;

	/* Enable Clock access to tim3 */
		// we already know how to check what clock this attached to
		// classic look at block diagram shite
	RCC->APB1ENR |= TIM3EN;


	/* Set prescaler */
	TIM3->PSC = 16000 - 1; // 16 000 000 000 / 16 000

	/* Set CH1 to input capture */
		// go to capture compare mode register 1 and check for how to do this
		// this is in our reference manual
		// look for input capture mode/ CC1S
	TIM3->CCMR1 |= CCER_CC1S;
		// can do a lot with this with adding filters
		// and extra configuratioins
		// DO THIS ON YOUR RUN!!!!!

	/* Set CH1 to capture at rising edge */
		// go to TIMx_CCER
		// be careful what timer you are brought to
		// default capture is at rising edge
		// check what bit you have to enable
	TIM3->CCER |= CCER_CC1E;

	/* Enable TIM3 */
	TIM3->CR1 |= CR1_CEN;


}
