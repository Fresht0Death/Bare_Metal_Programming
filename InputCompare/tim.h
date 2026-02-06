/*
 * tim.h
 *
 *  Created on: Jan 27, 2026
 *      Author: Freshmai
 */

#ifndef TIM_H_
#define TIM_H_

void tim2_1hz_init(void);
#define SR_UIF		(1U<<0)
void tim2_output_compare_pa5(void);
void tim3_pa6_input_capture(void);
#define SR_CC1IF      (1U<<1)


#endif /* TIM_H_ */
