/*
 * common.h
 *
 *  Created on: May 11, 2017
 *      Author: luoyang
 */
/*
 * for common header file
 *            define
 *            variable
 * */
#ifndef COMMON_H_
#define COMMON_H_

#include "derivative.h"
#include "stdio.h"
#include "ADC.h"
#include "SPI.h"
#include "I2C.h"
#include "PWM.h"
#include "SYSINIT.h"
#include "UART.h"
#include "OLED.h"
#include "DAC.h"
#include "mcg.h"
#include "arm_cm0.h"
#include "board.h"
/** PIN MAP
 *  funtion          pin       ALT
 *  UART0_TX         PTB1
 *  UART0_RX         PTB2
 *  SPI0_SS          PTA19
 *  SPI0_MISO        PTB15
 *  SPI0_MOSI        PTB16
 *  SPI0_SCK         PTB17
 *  DAC_SYNC         PTB12
 *  DAC_LDAC         PTB13
 *  I2C0_SCL         PTB3
 *  I2C0_SDA         PTB4
 *  
 */

/* Actual system clock frequency */
int mcg_clk_hz;
int mcg_clk_khz;
int core_clk_khz;
int periph_clk_khz;
int pll_clk_khz;
int uart0_clk_khz;


#endif /* COMMON_H_ */
