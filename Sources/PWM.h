/*
 * PWM.h
 *
 *  Created on: May 11, 2017
 *      Author: luoyang
 */

#ifndef PWM_H_
#define PWM_H_
#include "common.h"
/**
 * PULSE_GENERATE_PWM            PTB9        2 TPM0_CH2
 * */
#define PULSEMODULE   0
#define PULSECHANNEL  2
#define CLOCKHZ       20970000

void TPM0Init(int channel);
void PWMSetFrequency(int hz,int duty);
void PWMStart(void);
void PWMStop(void);



#endif /* PWM_H_ */
