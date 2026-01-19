/*
 * adc.h
 *
 *  Created on: Jan 19, 2026
 *      Author: Freshmai
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
uint32_t read_adc(void);
void start_conversion(void);
void pa1_adc_init(void);



#endif /* ADC_H_ */
