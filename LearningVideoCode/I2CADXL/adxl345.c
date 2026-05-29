/*
 * adxl345.c
 *
 *  Created on: May 26, 2026
 *      Author: Freshmai
 */


#include "adxl345.h"
#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"


// Global variable that stores return value from adxl
char data;
uint8_t dataVals[6];


void adxl_read_address(uint8_t reg){

	I2C2_byteRead(reg, DEVICE_ADDR ,&data);

}

void adxl_write(uint8_t reg, char value){

	char data[1];
	data[0] = value;

	I2C2_burstWrite(DEVICE_ADDR, reg, 1, data);

}

void adxl_read_values(uint8_t reg)
{
	I2C2_burstRead(DEVICE_ADDR, reg, 6, (char*)dataVals);

}


void adxl_init(void)
{
    I2C2_init();

    adxl_read_address(DEVID_R);

    printf("DEVID = 0x%02X\r\n", data);

    printf("After DEVID: SR1=0x%08lx SR2=0x%08lx PB10=%lu PB3=%lu\r\n",
           I2C2->SR1,
           I2C2->SR2,
           (GPIOB->IDR >> 10) & 1,
           (GPIOB->IDR >> 3) & 1);

    while (1) {}
}


/*
void adxl_init(void)
{

	/* Enable i2c module
	I2C2_init();

	/* Reed the DEV ID which should return to 0xE5
	adxl_read_address(DEVID_R);




	/* Set data format range to +-4g
	adxl_write(DATA_FORMAT_R, FOUR_G);

	/* Reset all bits
	adxl_write(POWER_CTRL_R, ADXL345_POWER_RESET);

	/* Configure the power control measure bit
	adxl_write(POWER_CTRL_R, SET_MEASURE_B);


}

*/

