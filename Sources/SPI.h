/*
 * SPI.h
 *
 *  Created on: May 11, 2017
 *      Author: luoyang
 */

#ifndef SPI_H_
#define SPI_H_

#include "common.h"
void SPIOInit();
void SPI0SendChar(unsigned char ch);
unsigned char SPI0GetChar();
void SPI0SendString(unsigned char *str);


#endif /* SPI_H_ */
