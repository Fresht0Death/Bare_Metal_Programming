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

#define SR2_BUSY         (1U<<1)
#define CR1_START        (1U<<8)
#define SR1_SB           (1U<<0)
#define SR1_ADDR         (1U<<1)
#define SR1_TXE          (1U<<7)
#define CR1_ACK          (1U<<10)
#define CR1_STOP         (1U<<9)
#define SR1_RXNE         (1U<<6)

#define SR1_BTF       (1U<<2)



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




void I2C1_byteRead(char saddr, char maddr, char* data)
{


	volatile int tmp;

	/* Wait until */
	while(I2C1->SR2 & (SR2_BUSY)){}

	/* Generate Start */
	I2C1->CR1 |= CR1_START;

	/* Wait until start flag is set */
	while(!(I2C1->SR1 & (SR1_SB))){}

	/* Transmit slave address + Write */
	I2C1->DR = saddr << 1;

	/* wait until addr flag is set */
	while(!(I2C1->SR1 & (SR1_ADDR))){}

	/* Clear address flag */
	tmp = I2C1->SR2;

	/* Send memory address */
	I2C1->DR = maddr;

	/* wait until transmitter empty */
	while(!(I2C1->SR1 & SR1_TXE)){}

	/* Generate restart */
	I2C1->CR1 |= CR1_START;

	/* wait until start flag is set */
	while(!(I2C1->SR1 & SR1_SB)){}

	/* Transmit slave address + Read */
	I2C1->DR = saddr << 1 | 1;

	/* Wait until addr flag is set */
	while(!(I2C1->SR1 & (SR1_ADDR))){}

	/* Disable Acknowledge */
	I2C1->CR1 &=~ CR1_ACK;

	/* clear address flag */
	tmp = I2C1->SR2;

	/* Generate stop after data recieved */
	I2C1->CR1 |= CR1_STOP;

	/* Wait until RXNE flag is set*/
	while(!(I2C1->SR1 & SR1_RXNE)){}

	/* Read data from DR */
	*data++ = I2C1->DR;

}

void I2C1_burstRead(char saddr, char maddr, int n, char* data)
{
	volatile int tmp;

	/* Wait until bus not busy */
	while(I2C1->SR2 & (SR2_BUSY)){}

	/* Generate start */
	I2C1->CR1 |= CR1_START;

	/* Wait until start flag is set */
	while(!(I2C1->SR1 & SR1_SB)){}

	/* Transmit slave address + Write */
	I2C1->DR = saddr << 1;

	/* Wait until addr flag is set */
	while(!(I2C1->SR1 & SR1_ADDR)){}

	/* CLear addr flag */
	tmp = I2C1->SR2;

	/* Wait until transmitter empty */
	while(!(I2C1->SR1 & SR1_TXE)){}

	/* Send memory address */
	I2C1->DR = maddr;

	/* Wait until transmitter empty */
	while(!(I2C1->SR1 & SR1_TXE)){}

	/* Generate restart */
	I2C1->CR1 |= CR1_START;

	/* wait until start flag is set */
	while(!(I2C1->SR1 & SR1_SB)){}

	/* Transmite slave address + Read */
	I2C1->DR = saddr << 1 |1;

	/* Wait until addr flag is set */
	while(!(I2C1->SR1 & (SR1_ADDR))){}

	/* Clear addr flag */
	tmp = I2C1->SR2;

	/* Enable acknowledge */
	I2C1->CR1 |= CR1_ACK;


	while(n > 0U)
	{
		/* if one byte */
		if(n == 1U)
		{
				/* Disable Acknowledge */
				I2C1->CR1 &=~ CR1_ACK;

				/* Generate Stop */
				I2C1->CR1 |= CR1_STOP;

				/* Wait until RXNE flag is set */
				while(!(I2C1->SR1 & SR1_RXNE)){}

				/* Read data from DR */
				*data++ = I2C1->DR;
				break;
		}
		else
		{
			/* Wait until RXNE flag is set */
			while(!(I2C1->SR1 & SR1_RXNE)){}

			/* Read data from DR */
			(*data++) = I2C1->DR;

			n--;


		}
	}


}

void i2c1_BurstWrite(char saddr, char maddr, int n, char* data)
{
	volatile int tmp;

	/* Wait until bus not busy */
	while(I2C1->SR2 & (SR2_BUSY)){}

	/* Generate start */
	I2C1->CR1 |= CR1_START;

	/* Wait until start flag is set */
	while(!(I2C1->SR1 & (SR1_ADDR))){}

	/* Transmit slave address */
	I2C1->DR = saddr << 1;

	/* Wait until addr flag is set */
	while(!(I2C1->SR1 & (SR1_ADDR))){}

	/* Send memory address */
	I2C1->DR = maddr;

	for(int i = 0; i < n; i++)
	{
		/* Wait until data register empty */
		while(!(I2C1->SR1 & (SR1_TXE))){}

		/* Transmit memory address */
		I2C1->DR = *data++;

	}

		/* Wait until transfer finished */
		while(!(I2C1->SR1 & (SR1_BTF))){}

	}


