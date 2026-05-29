/*
 * adxl345.h
 *
 *  Created on: May 26, 2026
 *      Author: Freshmai
 */

#ifndef ADXL345_H_
#define ADXL345_H_

#include "i2c.h"
#include <stdint.h>

#define DEVID_R					(0x00)
#define DEVICE_ADDR				(0x53)
#define DATA_FORMAT_R			(0x31)
#define DATA_START_ADDR			(0x32)
#define POWER_CTRL_R			(0x2D)

#define FOUR_G					(0x01)
#define ADXL345_POWER_RESET    (0x00)
#define SET_MEASURE_B			(0x08)


void adxl_init(void);
void adxl_read_values(uint8_t reg);


#endif /* ADXL345_H_ */
