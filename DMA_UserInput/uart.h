/*
 * uart.h
 *
 *  Created on: Jan 7, 2026
 *      Author: Freshmai
 */

#ifndef UART_H_
#define UART_H_
#include "stm32f4xx.h"
#include <stdint.h>

void uart2_tx_init(void);
char uart2_read(void);
void uart2_rxtx_init(void);
void dma1_stream6_init(uint32_t src, uint32_t dst, uint32_t len);


#endif /* UART_H_ */
