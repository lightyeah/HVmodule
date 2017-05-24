/*
 * DAC.c
 *
 *  Created on: May 11, 2017
 *      Author: luoyang
 */


#include "common.h"

/*
 * 选择通道输出电压
 * */
void NanoDACSetVoltage(unsigned char channel, float voltage)
{
	unsigned short data;
	data = (unsigned short)(voltage/5.0)*DACACCURACY;
	switch(channel)
	{
	case VOUTA:
		NanoDACWrite(COMMAND_WRITE_UPDATE,VOUTA,data);
		break;
	case VOUTD:
		NanoDACWrite(COMMAND_WRITE_UPDATE,VOUTD,data);
		break;
	default:
		break;
	}
}

void NanoDACWrite(unsigned char command,unsigned char address,unsigned short data )
{
	unsigned char sara, tom, tose;
	unsigned short victor;
	sara = command;
	sara = sara&0x0f;
	sara = sara<<4;
	
	tom = address;
	tom = tom&0x0f;
	
	sara = sara + tom;
	SYNCActive(1);
	delay_n_plus_1ms(1);
	SPI0SendChar(sara);
	victor = data;
	victor = victor & 0xff00;
	victor = victor>>8;
	sara = (unsigned char)victor;
	SPI0SendChar(sara);
	victor = data;
	victor = victor & 0x00ff;
	sara = (unsigned char)victor;
	SPI0SendChar(sara);
	delay_n_plus_1ms(1);
	SYNCActive(0);
	
}
/**
 * falling edge acctive
 */  
void SYNCActive(char sync)
{
	if(sync)
		GPIOB_PDOR &=~ 0x1000;//GPIO_PDOR_PDO(12);//logic 0
	else
		GPIOB_PDOR |= 0x1000;//GPIO_PDOR_PDO(12);//logic 1
		
}
