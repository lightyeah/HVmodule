/*
 * UART.h
 *
 *  Created on: May 11, 2017
 *      Author: luoyang
 */

#ifndef UART_H_
#define UART_H_

#include "common.h"

void UART0Init(int sysclk, int baud);
char UART0GetChar();
void UART0SendChar(char ch);
int UART0GetCharPresent();
unsigned char dtoa(unsigned char n);// 16½øÖÆ×ª»»
void UART0SendHex(unsigned char data);
void UART0SendString(char * str);
unsigned char Char2Num(unsigned char ch);
unsigned int TermGetNum(void);

#endif /* UART_H_ */
