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
#include "locale.h"
/** PIN MAP
 *  funtion                       pin        ALT
 *  UART0_TX                      PTB1        2
 *  UART0_RX                      PTB2        2
 *  SPI0_SS                       PTA19       3
 *  SPI0_MISO                     PTB15       3
 *  SPI0_MOSI                     PTB16       3
 *  SPI0_SCK                      PTB17       3
 *  DAC_SYNC                      PTB12       
 *  DAC_LDAC                      PTB13       
 *  I2C0_SCL                      PTB3        2
 *  I2C0_SDA                      PTB4        2
 *  PULSE_GENERATE_PWM            PTB9        2 TPM0_CH2
 *  HV_ADC                        PTA9        0 ADC0_SE2
 *
 */
typedef float hvtype;


#define  NORMALCLOCK   20970000//HZ
/***
 * when HV_R>= 2100 set HV_S = 0
 * */
#define  HVERROR       2000.0//V 保护电压
#define  HVMAX         1800.0//V  最大电压
#define  HVDEVIATION   40.0//V 实际电压与设置电压之间的误差范围

#define  DACMAX        5.0//DAC最大输出电压
#define  DACACCURACY   65536//16bit 精度
/* Actual system clock frequency */
int mcg_clk_hz;
int mcg_clk_khz;
int core_clk_khz;
int periph_clk_khz;
int pll_clk_khz;
int uart0_clk_khz;






#endif /* COMMON_H_ */
