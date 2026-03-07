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

#define CTRL_TICKINT		(1U<<1);



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


void systick_1hz_init(void)
{

	/* Reload with number of clocks per second */
//	SysTick->LOAD = SYSTICK_LOAD_VAL;


	// trying to slow this shit down
	/* TESTING */
	// 16 makes it go SUPER FAST
	// 16000 makes it go every second
	// 1600000 makes it go pretty fast too
	// 16000000 makes it go slower
	// 160000000000 even slower
	// 160000000000000000 too high man
	// 16777215 = max 24 bit number for unsigned obvi
	SysTick->LOAD = 16777215 - 1;

	/* clear systick current value register (BEST PRACTICE) */
	SysTick->VAL = 0;

	/* Enable systick and select internal clk src */
	SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC;




	/* Enable systick interrupt */
	SysTick->CTRL |= CTRL_TICKINT;


}




