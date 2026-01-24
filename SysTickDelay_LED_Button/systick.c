/*
 * systick.c
 *
 *  Created on: Jan 24, 2026
 *      Author: Freshmai
 */


// header file for our board
#include "stm32f4xx.h"

// macros
#define SYSTICK_LOAD_VAL    	16000 			// clock cycles per millisecond = 16 000 000 / 1000
#define CTRL_ENABLE				(1U<<0)         // bit 0 enables counter
#define CTRL_CLKS				(1U<<2)			// bit 2 enables processor clock
#define CTRL_FLAG				(1U<<16)        // bit 16 checks if counter is done




/*******************************************
 * 										   *
 * function: systickDelayMS(int delay)     *
 * 										   *
 * 	use: pass in a value for how long your *
 * 		 delay should be and then    	   *
 * 		 executes delay time			   *
 * 										   *
 *******************************************/

void systickDelayMS(int delay)
{

	/* Load in value for register to start at */
	SysTick->LOAD |= SYSTICK_LOAD_VAL;

	/* Clear systick current value register */
	SysTick->VAL = 0;

	/* Enable systick and select internal clk src */
	SysTick->CTRL = CTRL_ENABLE | CTRL_CLKS;

	// creating a delay loop
	for(int i = 0; i < delay; i++){

	/* wait while i until the COUNTFLAG is set */
		while((SysTick->CTRL & CTRL_FLAG) == 0){}
	}


	SysTick->CTRL = 0;




}
