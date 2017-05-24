/*
 * DAC.h
 *
 *  Created on: May 11, 2017
 *      Author: luoyang
 */

#ifndef DAC_H_
#define DAC_H_

#include "common.h"

#define COMMAND_NOP                         0b0000
#define COMMAND_WRITE_REGISTER              0b0001
#define COMMAND_UPDATE_DAC                  0b0010
#define COMMAND_WRITE_UPDATE                0b0011
#define COMMAND_POWER_ONOFF                 0b0100
#define VOUTA                               0b0001
#define VOUTD                               0b1000


void NanoDACSetVoltage(unsigned char channel, float voltage);
void NanoDACWrite(unsigned char command,unsigned char address,unsigned short data );
void SYNCActive(char sync);
#endif /* DAC_H_ */
