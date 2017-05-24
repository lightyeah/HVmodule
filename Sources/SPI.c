/*
 * SPI.c
 *
 *  Created on: May 11, 2017
 *      Author: luoyang
 */


#include "common.h"

//20170512  clock maybe 21MHZ
void SPI0Init()
{
	SPI0_C1 |= SPI_C1_SPE_MASK;
	SPI0_C1 |= SPI_C1_MSTR_MASK;//AS A MASTER  DEVICE
	SPI0_C1 &= ~SPI_C1_CPOL_MASK;//CLOCK POLARITY AS ACTIVE-HIGH SPI CLOCK (idles low)
	SPI0_C1 |= SPI_C1_CPHA_MASK;//CLOCK PHASE MIDDLE 
	SPI0_C1 &= ~SPI_C1_LSBFE_MASK;//DATA START WITH MSB
    SPI0_C2 &= ~SPI_C2_MODFEN_MASK;//SS pin function is generate-purpose IO
	//BT 131KHZ
	SPI0_BR |= 0x44;//set SPI_BR divisor (4+1)*32 = 160 0b 0100 0100	
}

void SPI0SendChar(unsigned char ch)
{
	while(!(SPI0_S & 0x20));
		SPI0_D = ch;
}

void SPI0SendString(unsigned char *str)
{
	while(*str != '\0')
	{
		SPI0SendChar((*str++)&0xff);
	}
}

unsigned char SPI0GetChar()
{
	while(!(SPI0_S&0x80));
	return SPI0_D;
}

