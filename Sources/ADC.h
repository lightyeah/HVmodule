/*
 * ADC.h
 *
 *  Created on: May 11, 2017
 *      Author: luoyang
 */

#ifndef ADC_H_
#define ADC_H_

#include "common.h"
/**
 * HV_ADC                        PTA9        0 ADC0_SE2
 * */
#define HVADCMODULE   0
#define HVADCCHANNEL  2


void ADC0Init();
int ADCGetHV();


#endif /* ADC_H_ */
