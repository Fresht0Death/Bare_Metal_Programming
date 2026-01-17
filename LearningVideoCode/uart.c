/*
 * uart.c
 *
 *  Created on: Jan 7, 2026
 *      Author: Freshmai
 */

#include "uart.h"

// symbolic names:
#define GPIOAEN    (1U<<0)		// GPIOAEN : set bit 0  as a 1
#define UART2EN	   (1U<<17)     // UART2EN : set bit 17 as a 1
#define SYSFREQ    16000000     // 16 MHZ
#define APB1_CLK   SYSFREQ

#define UART_BAUDRATE  115200

#define CR1_TE        (1U<<3)
#define CR1_UE        (1U<<13)
#define SR_TXE  	  (1U<<7)

#define CR1_RE        (1U<<2)
#define SR_RXNE		  (1U<<5)



/* function prototypes */
static void uart_set_baudrate(USART_TypeDef *USARTTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);
void uart2_write(int ch);


int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;

}

void uart2_rxtx_init(void)
{

	/*++++ Configuration uart gpio pin ++++*/
	/*    Enable clock access to GPIOA         */
	RCC->AHB1ENR |= GPIOAEN;

	/*    Set PA2 mode to alternate function mode (TX)    */
	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |= (1U<<5);


	/*    Set PA2 alternate function type to UART_TX(AF07 = 0111) (TX)    */
	GPIOA->AFR[0] |= (1U<<8); // setting pin 8 of the low half of the alt. func. reg.
	GPIOA->AFR[0] |=(1U<<9);
	GPIOA->AFR[0] |=(1U<<10);
	GPIOA->AFR[0] &=~(1U<<11);

	/*    Set PA3 mode to alternate function mode (RX)   */
	GPIOA->MODER &=~(1U<<6);
	GPIOA->MODER |= (1U<<7);

	/*    Set PA3 alternate function type to UART_RX(AF07 = 0111) (RX)    */
	GPIOA->AFR[0] |= (1U<<12); // setting pin 12 of the low half of the alt. func. reg.
	GPIOA->AFR[0] |=(1U<<13);
	GPIOA->AFR[0] |=(1U<<14);
	GPIOA->AFR[0] &=~(1U<<15);




	/*++++ Configuration uart module   ++++*/
	/*    Enable clock access to UART2     */
	RCC->APB1ENR |= UART2EN;

	/*    Configure baudrate               */
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	/*    Configure the transfer direction */
	USART2->CR1 = (CR1_TE | CR1_RE);


	/*    Enable UART module               */
	USART2->CR1 |= CR1_UE;



}

char uart2_read(void)
{
	/*    Make sure the receive data register is NOT empty    */
	while(!(USART2->SR & SR_RXNE)){}

	/* return the content of the data register */
	return USART2->DR;



}

void uart2_tx_init(void)
{

	/*++++ Configuration uart gpio pin ++++*/
	/*    Enable clock access to GPIOA         */
	RCC->AHB1ENR |= GPIOAEN;

	/*    Set PA2 mode to alternate function mode    */
	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	/*    Set PA2 alternate function type to UART_TX(AF07 = 0111)    */
	GPIOA->AFR[0] |= (1U<<8); // setting pin 8 of the low half of the alt. func. reg.
	GPIOA->AFR[0] |=(1U<<9);
	GPIOA->AFR[0] |=(1U<<10);
	GPIOA->AFR[0] &=~(1U<<11);


	/*++++ Configuration uart module   ++++*/
	/*    Enable clock access to UART2     */
	RCC->APB1ENR |= UART2EN;

	/*    Configure baudrate               */
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	/*    Configure the transfer direction */
	USART2->CR1 = CR1_TE;

	/*    Enable UART module               */
	USART2->CR1 |= CR1_UE;



}

void uart2_write(int ch)
{
	/*    1. Make sure transmit data register is empty    */
	while(!(USART2->SR & SR_TXE)){}
	/*    2. Write to transmit data register    */

	USART2->DR = ch & 0xFF; // we and with FF because we want to transmit 8-bits





}



static void uart_set_baudrate(USART_TypeDef *USARTTx, uint32_t PeriphClk, uint32_t BaudRate)
{

	USARTTx->BRR = compute_uart_bd(PeriphClk, BaudRate);


}



static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{

	 return ((PeriphClk + (BaudRate / 2U)) / BaudRate);



}
