/*
 * i2c.h
 *
 *  Created on: Mar 10, 2026
 *      Author: Freshmai
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

void I2C2_init(void);
void I2C2_byteRead(char maddr, char saddr, char* data);
void I2C2_burstRead(char saddr, char maddr, int n, char* data);
void I2C2_burstWrite(char saddr, char maddr, int n,char* data);
void I2C2_start_only_test(void);
void I2C2_probe(uint8_t saddr);



#endif /* I2C_H_ */
