/*
 * i2c.c
 *
 *  Created on: Mar 10, 2026
 *      Author: Freshmai
 */


#include "stm32f4xx.h"
#include <stdio.h>



/* User defined Macros -------------------------*/

// for init function
#define GPIOBEN					(1U<<1)
#define OPENDRAINPB3			(1U<<3)
#define OPENDRAINPB10			(1U<<10)
#define I2C2EN					(1U<<22)
#define APB1RESETI2C2			(1U<<22)
#define I2C216MHz				(1<<4)
#define I2C2CCR100MHz			(80)
#define I2C2TRISE				(17)
#define I2C2CR1EN				(1U<<0)

// used for the read byte function
#define I2C2SR2BUSBUSY			(1U<<1)
#define I2C2CR1STARTGEN			(1U<<8)
#define I2C2SR1SB				(1U<<0)
#define I2C2SR1ADDRFLAG			(1U<<1)
#define I2C2SR1TXE				(1U<<7)
#define I2C2CR1ACK				(1U<<10)
#define I2C2CR1STOP				(1U<<9)
#define I2C2SR1RXNE				(1U<<6)
#define I2C2SR1BTF				(1U<<2)
#define I2C2SR1AF 				(1U << 10)


/*-------------------------------------------------*
 * 												   *
 * Function: I2C_init							   *
 * 												   *
 * Return: void									   *
 * 												   *
 * Parameters: void								   *
 * 												   *
 * Purpose: start up function for I2C2, where	   *
 * 	pins PB3 and PB10 are used for SDA and 		   *
 * 	SCL, respectively.							   *
 * 												   *
 *-------------------------------------------------*/
void I2C2_init(void){




	// Enable clock access to GPIOB

	RCC->AHB1ENR |= GPIOBEN;

	// PB3 = I2C2_SDA, PB10 = I2C2_SCL

	// Set mode to alternate function: MODER bits = 10

	GPIOB->MODER &= ~((3U << (3 * 2)) | (3U << (10 * 2)));

	GPIOB->MODER |=  ((2U << (3 * 2)) | (2U << (10 * 2)));

	// Set output type to open-drain

	GPIOB->OTYPER |= (1U << 3) | (1U << 10);

	// Set pull-up: PUPDR bits = 01

	GPIOB->PUPDR &= ~((3U << (3 * 2)) | (3U << (10 * 2)));

	GPIOB->PUPDR |=  ((1U << (3 * 2)) | (1U << (10 * 2)));

	// Set alternate function AF4 for PB3 and PB10

	GPIOB->AFR[0] &= ~(0xFU << (3 * 4));

	GPIOB->AFR[0] |=  (4U   << (3 * 4));

	GPIOB->AFR[1] &= ~(0xFU << ((10 - 8) * 4));

	GPIOB->AFR[1] |=  (4U   << ((10 - 8) * 4));



	// Enabling clock access to the I2C2 peripheral
	RCC->APB1ENR |= I2C2EN;

	// Reset I2C2
	RCC->APB1RSTR |= APB1RESETI2C2;
	RCC->APB1RSTR &= ~APB1RESETI2C2;

	// Disable I2C before configuring timing
	I2C2->CR1 &= ~I2C2CR1EN;

	// Set peripheral clock frequency to 16 MHz
	I2C2->CR2 &= ~(0x3FU);
	I2C2->CR2 |= 16;

	// Set I2C Standard Mode, 100 kHz clock
	I2C2->CCR = I2C2CCR100MHz;

	// Set rise time
	I2C2->TRISE = I2C2TRISE;

	// Required: OAR1 bit 14 must be kept at 1
	I2C2->OAR1 = (1U << 14);

	// Enable I2C
	I2C2->CR1 |= I2C2CR1EN;

}


// mem. addr // slave addr  // data to be returned
void I2C2_byteRead(char maddr, char saddr, char* data){

	volatile int tmp;


	while(I2C2->SR2 & I2C2SR2BUSBUSY){/* get stuck here while communication ongoing on the bus */}

	uint32_t timeout = 1000000;

	I2C2->CR1 |= I2C2CR1STARTGEN;

	while (!(I2C2->SR1 & I2C2SR1SB)) {
	    if (--timeout == 0) {
	        printf("START timeout: CR1=0x%08lx CR2=0x%08lx SR1=0x%08lx SR2=0x%08lx\r\n",
	               I2C2->CR1, I2C2->CR2, I2C2->SR1, I2C2->SR2);
	        printf("GPIOB IDR=0x%08lx PB10/SCL=%lu PB3/SDA=%lu\r\n",
	               GPIOB->IDR,
	               (GPIOB->IDR >> 10) & 1,
	               (GPIOB->IDR >> 3) & 1);
	        return;
	    }
	}


	// Transmit slave address + Write
	I2C2->DR = saddr << 1;

	uint32_t addr_timeout = 1000000;

	while (!(I2C2->SR1 & I2C2SR1ADDRFLAG)) {
	    if (--addr_timeout == 0) {
	        printf("ADDR timeout in byteRead\r\n");
	        printf("maddr=0x%02X saddr=0x%02X sent_write_byte=0x%02X\r\n",
	               (unsigned char)maddr,
	               (unsigned char)saddr,
	               (unsigned char)(saddr << 1));

	        printf("CR1=0x%08lx CR2=0x%08lx SR1=0x%08lx SR2=0x%08lx\r\n",
	               I2C2->CR1, I2C2->CR2, I2C2->SR1, I2C2->SR2);

	        printf("GPIOB IDR=0x%08lx PB10/SCL=%lu PB3/SDA=%lu\r\n",
	               GPIOB->IDR,
	               (GPIOB->IDR >> 10) & 1,
	               (GPIOB->IDR >> 3) & 1);

	        I2C2->CR1 |= I2C2CR1STOP;
	        I2C2->SR1 &= ~I2C2SR1AF;
	        return;
	    }
	}

	// Clear addr flag
	tmp = I2C2->SR1;
	tmp = I2C2->SR2;

	// Send memory address all at once to data register for holding
	I2C2->DR = maddr;

	// Wait until byte transfer finished
	while(!(I2C2->SR1 & I2C2SR1BTF)){}

	// Generate restart
	I2C2->CR1 |= I2C2CR1STARTGEN;

	// Wait until start flag is set
	while(!(I2C2->SR1 & (I2C2SR1SB))){}

	// Transmit Slave address + Read
	I2C2->DR = saddr << 1 | 1;

	// Wait until the address flag is set
	while(!(I2C2->SR1 & (I2C2SR1ADDRFLAG))){}

	// Disable Acknowledge
	I2C2->CR1 &=~ I2C2CR1ACK;

	// Clear addr flag
	tmp = I2C2->SR1;
	tmp = I2C2->SR2;

	// Generate stop condition after data received
	I2C2->CR1 |= I2C2CR1STOP;

	// Wait until RXNE flag is set
	while(!(I2C2->SR1 & (I2C2SR1RXNE))){}

	// Read data from DR
	(*data++) = I2C2->DR;

}

void I2C2_burstRead(char saddr, char maddr, int n, char* data){

	volatile int tmp;

	while(I2C2->SR2 & I2C2SR2BUSBUSY){/* get stuck here while communication ongoing on the bus */}

	// Generate Start
	I2C2->CR1 |= I2C2CR1STARTGEN;

	// Wait until start flag is set
	while(!(I2C2->SR1 & (I2C2SR1SB))){}

	// Transmit slave address + Write
	I2C2->DR = saddr << 1;

	// Wait until address flag is set
	while(!(I2C2->SR1 & (I2C2SR1ADDRFLAG))){}

	// Clear addr flag
	tmp = I2C2->SR1;
	tmp = I2C2->SR2;

	// Wait until data register is empty
	while(!(I2C2->SR1 & I2C2SR1TXE)){}

	// Send memory address all at once to data register for holding
	I2C2->DR = maddr;


	// Wait until data register is empty
	while(!(I2C2->SR1 & I2C2SR1TXE)){}


	// Generate restart
	I2C2->CR1 |= I2C2CR1STARTGEN;

	// Wait until start flag is set
	while(!(I2C2->SR1 & (I2C2SR1SB))){}

	// Transmit Slave address + Read
	I2C2->DR = saddr << 1 | 1;

	// Wait until the address flag is set
	while(!(I2C2->SR1 & (I2C2SR1ADDRFLAG))){}

	// Clear addr flag
	tmp = I2C2->SR1;
	tmp = I2C2->SR2;

	// Enable ACK
	I2C2->CR1 |= I2C2CR1ACK;

	while(n >0U){


		if(n == 1U){

			// Disable Acknowledge
			I2C2->CR1 &=~ I2C2CR1ACK;

			// Generate stop condition after data received
			I2C2->CR1 |= I2C2CR1STOP;

			// Wait until RXNE flag is set
			while(!(I2C2->SR1 & (I2C2SR1RXNE))){}

			// Read data from DR
			(*data++) = I2C2->DR;

			break;

		}else
		{
			// Wait until RXNE flag is set
			while(!(I2C2->SR1 & (I2C2SR1RXNE))){}

			// Read data from DR
			(*data++) = I2C2->DR;

			n--;
		}

	}

}


void I2C2_burstWrite(char saddr, char maddr,  int n ,char* data){

	volatile int tmp;

	uint32_t timeout = 1000000;

	while(I2C2->SR2 & I2C2SR2BUSBUSY)
	{
	    if (--timeout == 0)
	    {
	        printf("burstWrite BUSY timeout: CR1=0x%08lx CR2=0x%08lx SR1=0x%08lx SR2=0x%08lx\r\n",
	               I2C2->CR1, I2C2->CR2, I2C2->SR1, I2C2->SR2);

	        printf("GPIOB IDR=0x%08lx PB10/SCL=%lu PB3/SDA=%lu\r\n",
	               GPIOB->IDR,
	               (GPIOB->IDR >> 10) & 1,
	               (GPIOB->IDR >> 3) & 1);

	        return;
	    }
	}

	// Generate Start
	I2C2->CR1 |= I2C2CR1STARTGEN;

	// Wait until start flag is set
	while(!(I2C2->SR1 & (I2C2SR1SB))){}

	// Transmit slave address + Write
	I2C2->DR = saddr << 1;

	// Wait until address flag is set
	while(!(I2C2->SR1 & (I2C2SR1ADDRFLAG))){}

	// Clear addr flag
	tmp = I2C2->SR1;
	tmp = I2C2->SR2;

	// Wait until data register is empty
	while(!(I2C2->SR1 & I2C2SR1TXE)){}


	// Send memory address all at once to data register for holding
	I2C2->DR = maddr;


	for (int i = 0; i < n; i++){

		// Wait until data register is empty
		while(!(I2C2->SR1 & I2C2SR1TXE)){}

		// Transmit memory address
		I2C2->DR = *data++;


	}

	// Wait until Byte Transfer finished (BTF)
	while(!(I2C2->SR1 & I2C2SR1BTF)){}


	// Generate a stop condition
	I2C2->CR1 |= I2C2CR1STOP;

}


void I2C2_start_only_test(void)
{
    printf("Before START: SR1=0x%08lx SR2=0x%08lx PB10=%lu PB3=%lu\r\n",
           I2C2->SR1,
           I2C2->SR2,
           (GPIOB->IDR >> 10) & 1,
           (GPIOB->IDR >> 3) & 1);

    I2C2->CR1 |= I2C2CR1STARTGEN;

    for (volatile int i = 0; i < 100000; i++) {}

    printf("After START request: CR1=0x%08lx SR1=0x%08lx SR2=0x%08lx PB10=%lu PB3=%lu\r\n",
           I2C2->CR1,
           I2C2->SR1,
           I2C2->SR2,
           (GPIOB->IDR >> 10) & 1,
           (GPIOB->IDR >> 3) & 1);

    while (1) {}
}

void I2C2_probe(uint8_t saddr)
{
    volatile int tmp;

    while (I2C2->SR2 & I2C2SR2BUSBUSY) {}

    I2C2->CR1 |= I2C2CR1STARTGEN;

    while (!(I2C2->SR1 & I2C2SR1SB)) {}

    I2C2->DR = saddr << 1;

    uint32_t timeout = 1000000;

    while (!(I2C2->SR1 & I2C2SR1ADDRFLAG)) {
        if (--timeout == 0) {
            printf("Probe 0x%02X: NACK SR1=0x%08lx SR2=0x%08lx\r\n",
                   saddr, I2C2->SR1, I2C2->SR2);

            I2C2->CR1 |= I2C2CR1STOP;
            I2C2->SR1 &= ~I2C2SR1AF;
            return;
        }
    }

    tmp = I2C2->SR1;
    tmp = I2C2->SR2;

    I2C2->CR1 |= I2C2CR1STOP;

    printf("Probe 0x%02X: ACK\r\n", saddr);
}



