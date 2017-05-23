/*
 * ADC.c
 *
 *  Created on: May 11, 2017
 *      Author: luoyang
 */

#include "common.h"

void ADC0Init()
{
	ADC0_CFG1 |= (ADC_CFG1_ADIV(0)|ADC_CFG1_ADLSMP_MASK|ADC_CFG1_MODE(2));
	ADC0_SC3 |= ADC_SC3_ADCO_MASK;
	ADC0_SC1A = ADC_SC1_ADCH(2);
}

int ADCGetHV()
{
	while((ADC0_SC1A&ADC_SC1_COCO_MASK)!=ADC_SC1_COCO_MASK);		
	int temp = (int)ADC0_RA;
	ADC0_SC1A&=~ADC_SC1_COCO_MASK;
	return temp;
	
}
