/*
 * systick.c
 *
 *  Created on: Jan 22, 2026
 *      Author: Freshmai
 */


#include "stm32f4xx.h"

// defining our macros
#define SYSTICK_LOAD_VAL 16000
#define CTRL_ENABLE      (1U<<0)
#define CTRL_CLKSRC       (1U<<2) // this is to use the systems clock
#define CTRL_COUNTFLAG   (1U<<16) // 1 in 16 means we have timed out

#define ONE_SEC_LOAD            16000000
#define CTRL_TICKINT            (1U<<1)




// will take an argue. for how long our delay should be
// and calculate and execute it
void systickDelayMS(int delay)
{

	/* Reload with number of clocks per millisecond */
	SysTick->LOAD = SYSTICK_LOAD_VAL;

	/* Clear systick current value register */
	SysTick->VAL = 0;
	/* Enable systick and select internal clk src */
	SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC;

	// creating a delay loop
	for(int i = 0; i < delay; i++){
	/* Wait until the COUNTFLAG is set */
		while((SysTick->CTRL & CTRL_COUNTFLAG) == 0){}
	}

	SysTick->CTRL = 0;

}

void systick_1hz_interrupt(void)
{

	SysTick->LOAD = ONE_SEC_LOAD - 1;


	/* Clear systick  crrent value register*/
	SysTick->VAL = 0;

	/* Enable systick and seleted internal clk src */
	SysTick->CTRL = CTRL_ENABLE |CTRL_CLKSRC;

	/* Enable systick interrupt */
	SysTick->CTRL |= CTRL_TICKINT;






}

