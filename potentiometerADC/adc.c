/*
 * adc.c
 *
 *  Created on: Jan 19, 2026
 *      Author: Freshmai
 */



#include "stm32f4xx.h"


#define GPIOAEN					(1U<<0)
#define ADC1EN					(1U<<8)
#define ADC_CH1					(1U<<0)
#define ADC_SEQ_LEN_1   		0x00
#define CR2_ADDON				(1U<<0)
#define ADC1_CR2_SWSTART		(1<<30)
#define SR_EOC					(1U<<1)


void pa1_adc_init(void){

	/**** Configure the ADC GPIOA pin ***/
	/* Enable clock access to GPIOA */
	RCC->AHB1ENR |= GPIOAEN;
	/* Set the mode of PA1 to analog mode which is done in the mode register */
	GPIOA->MODER |= (1<<2);
	GPIOA->MODER |= (1<<3);

	/*** Configure the ADC module/peripheral ***/
	RCC->APB2ENR |= ADC1EN;

	/* Conversion sequence starts */

	ADC1->SQR3 = ADC_CH1;

	/* Conversion sequence length */
	ADC1->SQR1 = ADC_SEQ_LEN_1;


	/* Enable the ADC module */

	ADC1->CR2 |= CR2_ADDON;


}

void start_conversion(void){

	/* Start conversion */
	ADC1->CR2 |= ADC1_CR2_SWSTART;

}

uint32_t read_adc(void){

	while(!(ADC1->SR & SR_EOC)){}

	return (ADC1->DR);

}



