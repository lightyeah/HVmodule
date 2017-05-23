/*
 * UART.h
 *
 *  Created on: May 11, 2017
 *      Author: luoyang
 */

#ifndef UART_H_
#define UART_H_

#include "common.h"


#ifdef NORMALCLOCK
void UART0Init_(int baud);
#endif

#ifndef NORMALCLOCK
void UART0Init(int sysclk, int baud);
#endif

char UART0GetChar();
void UART0SendChar(char ch);
int UART0GetCharPresent();
unsigned char dtoa(unsigned char n);// 16½øÖÆ×ª»»
void UART0SendHex(unsigned char data);
void UART0SendString(char * str);
unsigned int Char2Num(unsigned char ch);
unsigned int TermGetNum(void);
void CommandGetData(char commandaddress,char data,int dataaddress);//
void UARTCommandOutput();//
#endif /* UART_H_ */
