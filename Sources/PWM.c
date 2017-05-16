/*
 * PWM.c
 *
 *  Created on: May 11, 2017
 *      Author: luoyang
 */

#include "common.h"

/**
 * select channal on moduel TPM0 to initialize
 * */
int PwmClockHz = 0;

void TPM0Init(int channel)
{
	TPM0_SC |= (TPM_SC_CMOD(1)|TPM_SC_PS(7));//PWMCOUNTER PRESCALE 128
	PwmClockHz = 20970000/128;
	TPM0_MOD = 0x00;
	TPM0_CNT = 0x00;
	switch(channel)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		TPM0_C4V = 0x00;
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	default:
		break;
	}
}

/**
 * set period with parameters moudel and frequence and duty
 * */
void PWMSetFrequency(int hz, int duty)
{
	TPM0_MOD = PwmClockHz/hz;
	TPM0_C4V = (PwmClockHz*duty)/(100*hz);
	//TPM0_C2SC |= ();
}

void PWMStart(void)
{
	TPM0_C2SC |= (TPM_CnSC_MSB_MASK|TPM_CnSC_ELSB_MASK);
}

void PWMStop(void)
{
	TPM0_C2SC &= ~(TPM_CnSC_MSB_MASK|TPM_CnSC_ELSB_MASK);
}
