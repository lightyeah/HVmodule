/*
 * SYSINIT.h
 *
 *  Created on: May 11, 2017
 *      Author: luoyang
 */

#ifndef SYSINIT_H_
#define SYSINIT_H_
#include "common.h"


void SystemInit();//系统初始化
/* init success return 0
 * fail return 1
 * */
int ClockInit();
int ADCInit();
int I2CInit();
int IOInit();
int SPIInit();
int UARTInit();
int PWMInit();
int OLEDInit();
int DACInit();

void delay(void);
void delay_n_plus_100ms(unsigned char delay_number);
void delay_n_plus_1ms(unsigned char delay_number);

unsigned int mathmo(int a);//数值取模
#endif /* SYSINIT_H_ */
