/*
 * i2c.c
 *
 *  Created on: Mar 10, 2026
 *      Author: Freshmai
 */


#include "stm32f4xx.h"





#define GPIOBEN     (1U<<1)
#define I2C1EN      (1U<<21)
#define I2C_100KHZ  80  // OB 0101 0000 = decimal 80
#define SD_MODE_MAX_RISE_TIME 17
#define CR1_PE (1U<<0)


/*Pinout
	PB8 --- SCL
	PB9 --- SDA
 */
void I2C1_init(void)
{
	/* Enable clockes to GPIOB */
	RCC->AHB1ENR |= GPIOBEN;

	/* Set PB8 and PB9 mode to alt-function mode */
	GPIOB->MODER &=~ (1U<<16); // for pb8
	GPIOB->MODER |=  (1U<<17);

	GPIOB->MODER &=~ (1U<<18); // for pb9
	GPIOB->MODER |=  (1U<<19);

	/* Set PB8 and PB9 output type to open drain */
		// go to OTYPER - output type register
	GPIOB->OTYPER |= (1U<<8); // open drain for pb8
	GPIOB->OTYPER |= (1U<<9);  // open drain for pb9

	/* Enable Pullup for PB8 and PB9 */
		// go to PUPDR - pull up pull down register
		// look at truth table about how to set it
	GPIOB->PUPDR |= (1U<<16); // set: pb8
	GPIOB->PUPDR &=~(1U<<17);

	GPIOB->PUPDR |= (1U<<18); // set: pb9
	GPIOB->PUPDR &=~(1U<<19);

	/* Enable clock access to I2C1 */
	RCC->APB1ENR |= I2C1EN;

	/* Enter reset mode */
	I2C1->CR1 |= (1U<<15);

	/* Come out of reset mode */
	I2C1->CR1 &=~ (1U<<15);

	/* Set new frequency for I2C */
	I2C1->CR2 |= (1U<<4); // 16 Mhz
	 // how do you wrtie 16Mhz then?
	 //set frequency which is just the binary of the number


	/* Set clock to Standard Mode */
	I2C1->CCR = I2C_100KHZ;
	I2C1->TRISE = SD_MODE_MAX_RISE_TIME;
		// go to ccr register
		// set ccr register to 100KHz
		// set rise time to 17


	/* Enable I2C */
	I2C1->CR1 |= CR1_PE;



}


