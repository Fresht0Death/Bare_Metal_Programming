/*
 * spi.c
 *
 *  Created on: Jun 11, 2026
 *      Author: Freshmai
 */




// spi.c

#include "spi.h"
#include "stm32f4xx.h"

//Defined macros
#define SPI1EN            (1U<<12)
#define GPIOAEN           (1U<<0)
#define SR_TXE        	  (1U<<1)
#define SR_BUSY     	  (1U<<7)
#define SR_RXNE    	 	  (1U<<0)




/*--- Pin Configurations ---*
 *	PA5 -> CLK              *
 *	PA6 -> MISO             *
 *	PA7 -> MOSI             *
 *	PA9 -> Slave select     *
*---------------------------*/




void spi_gpio_init(void)
{
	/* Enable clock acces to GPIOA */
	RCC->AHB1ENR |= GPIOAEN;

	/* Enable gpio pins to alt function mode to the pins */
	// PA5
	GPIOA->MODER &=~ (1U<<10);
	GPIOA->MODER |=  (1U<<11);

	// PA6
	GPIOA->MODER &=~ (1U<<12);
	GPIOA->MODER |=  (1U<<13);

	// PA7
	GPIOA->MODER &=~ (1U<<14);
	GPIOA->MODER |=  (1U<<15);

	/* Set PA9 to output pin */
	GPIOA->MODER |= (1U<<18);
	GPIOA->MODER &=~(1U<<19);


	/* Set PA5, PA6, PA7 alternate function type to SPI1 */
	GPIOA->AFR[0] |= (1U<<20);
	GPIOA->AFR[0] &=~(1U<<21);
	GPIOA->AFR[0] |= (1U<<22);
	GPIOA->AFR[0] &=~(1U<<23);

	GPIOA->AFR[0] |= (1U<<24);
	GPIOA->AFR[0] &=~(1U<<25);
	GPIOA->AFR[0] |= (1U<<26);
	GPIOA->AFR[0] &=~(1U<<27);

	GPIOA->AFR[0] |= (1U<<28);
	GPIOA->AFR[0] &=~(1U<<29);
	GPIOA->AFR[0] |= (1U<<30);
	GPIOA->AFR[0] &=~(1U<<31);

}

void spi_config(void)
{

	/* Enable clock access to SPI1 */
	RCC->APB2ENR |= SPI1EN;

	/* Set PCLk / 4 */
	SPI1->CR1 |= (1U<<3);
	SPI1->CR1 &=~(1U<<4);
	SPI1->CR1 &=~(1U<<5);

	/* Set CPOL and CPHA to 1 */
	SPI1->CR1 |= (1U<<0);
	SPI1->CR1 |= (1U<<1);

	/* Enable full duplex */
	SPI1->CR1 &=~(1U<<10);

	/* Seet MSB first */
	SPI1->CR1 &=~(1U<<7);

	/* Set Mode to MASTER */
	SPI1->CR1 |= (1U<<2);

	/* Set 8 bit data mode */
	SPI1->CR1 &=~(1U<<11);

	/* Select software slave management by
		setting SSM = 1 and SSI = 1 */
	SPI1->CR1 |= (1<<8);
	SPI1->CR1 |= (1<<9);

	/* Setup the SPI module */
	SPI1->CR1 |= (1U<<6);

}



void spi1_transmit(uint8_t *data/* buffer data we want to transmit */, uint32_t size)
{
	uint32_t i = 0;
	uint8_t temp;

	while(i < size)
	{
		/* Wait until TXE is set */
		while(!(SPI1->SR & (SR_TXE))){}

		/* Write the data to data register */
		SPI1->DR = data[i];
		i++;

	}

	/* Wait until TXE is set */
	while(!(SPI1->SR & (SR_TXE))){}

	/* Wait for BUSY flag to reset*/
	while(SPI1->SR & (SR_BUSY)){}

	/* Clear the OVR flag */
	temp = SPI1->DR;
	temp = SPI1->SR;

}


void spi1_receive(uint8_t *data, uint32_t size)
{
	while(size)
	{
		/* Send dummy data */
		SPI1->DR = 0;

		/* Wait for RXNE flag to be set */
		while(!(SPI1->SR & (SR_RXNE))){}

		/* Read data from data register */
		*data++ = (SPI1->DR);

		size--;

	}

}

void cs_enable(void)
{
	/* Set gpio pin 9 to low */
	GPIOA->ODR &=~ (1U<<9);

}

void cs_disable(void)
{
	/* Set gpio pin 9 to low */
	GPIOA->ODR |= (1U<<9);

}
