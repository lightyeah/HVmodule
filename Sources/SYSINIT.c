/*
 * SYSINIT.c
 *
 *  Created on: May 11, 2017
 *      Author: luoyang
 */

#include "common.h"

void SystemInit()
{
	/*hardware Initialize*/
	ClockInit();//20170512 ?? clock maybe 21MHZ
	IOInit();
	asm("CPSIE i");//全局中断开启
	//NVIC_ISER |= NVIC_ISER_SETENA(12);//UART0 STATUS AND ERROR 
	NVIC_ISER |= 0x1000;
	UARTInit();
	SPIInit();
	ADCInit();
	PWMInit();
	
	/*software Initialize*/
	DACInit();
	
}

int ClockInit()
{
    // releases hold with ACKISO:  Only has an effect if recovering from VLLS1, VLLS2, or VLLS3
    // if ACKISO is set you must clear ackiso before calling pll_init 
    //    or pll init hangs waiting for OSC to initialize
    // if osc enabled in low power modes - enable it first before ack
    // if I/O needs to be maintained without glitches enable outputs and modules first before ack.
#ifndef NORMALCLOCK
    if (PMC_REGSC &  PMC_REGSC_ACKISO_MASK)
    PMC_REGSC |= PMC_REGSC_ACKISO_MASK;
    /* Ramp up the system clock */
    /* Set the system dividers */    
    SIM_CLKDIV1 = (0 | SIM_CLKDIV1_OUTDIV1(0) | SIM_CLKDIV1_OUTDIV4(1));
    mcg_clk_hz =  fei_fee(CLK0_FREQ_HZ,HIGH_GAIN,CLK0_TYPE);
    if (mcg_clk_hz < 0x100)
             while(1);
    uart0_clk_khz = mcg_clk_hz/(2*1000); // UART0 clock frequency will equal half the PLL frequency
	/*
         * Use the value obtained from the pll_init function to define variables
	 * for the core clock in kHz and also the peripheral clock. These
	 * variables can be used by other functions that need awareness of the
	 * system frequency.
	 */
     mcg_clk_khz = mcg_clk_hz / 1000;
  	 core_clk_khz = mcg_clk_khz / (((SIM_CLKDIV1 & SIM_CLKDIV1_OUTDIV1_MASK) >> 28)+ 1);
     periph_clk_khz = core_clk_khz / (((SIM_CLKDIV1 & SIM_CLKDIV1_OUTDIV4_MASK) >> 16)+ 1);  
#endif
     SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1); // select the FLLFLLCLK as UART0 clock source
     SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);//select the MCGFLLCLK as TPM clock source
     SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;//enable uart0 clock gate
     SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;//ENABLE SPI0 CLOCK GATE
     SIM_SCGC4 |= SIM_SCGC4_I2C0_MASK;//enable i2c clock gate
     SIM_SCGC5 |= (SIM_SCGC5_PORTA_MASK|SIM_SCGC5_PORTB_MASK);//ENABLE PORTA PORTB CLOCK GATE
     SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;//enable TPM0 clock gate
     SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;//enable ADC0 clock gate
    
	return 0;
}

int ADCInit()
{
	ADC0Init();
	return 0;
}

int I2CInit()
{
	
	return 0;
}
/**
 * IO initialize 
 * funtion: select pin for its alt function  
 */
int IOInit()
{
	/* PTB1 uart0_tx alt2
	 * PTB2 uart0_rx alt2*/
	PORTB_PCR1 |= PORT_PCR_MUX(2);
	PORTB_PCR2 |= PORT_PCR_MUX(2);
	/* PTA19 SPI0_SS
	 * PTB15 SPI0_MISO
	 * PTB16 SPI0_MOSI
	 * PTB17 SPI0_SCK
	 * PTB12 SYNC
	 * PTB13 LDAC
	 * */
	PORTB_PCR15 |= PORT_PCR_MUX(3);
	PORTB_PCR15 |= PORT_PCR_PS_MASK + PORT_PCR_PE_MASK;
	PORTB_PCR16 |= PORT_PCR_MUX(3);
	PORTB_PCR16 |= PORT_PCR_PS_MASK + PORT_PCR_PE_MASK;
	PORTB_PCR17 |= PORT_PCR_MUX(3);
	PORTB_PCR17 |= PORT_PCR_PS_MASK + PORT_PCR_PE_MASK;
	
	PORTA_PCR19 |= PORT_PCR_MUX(1);//GPIO output as RESET and enable the pullup resister
	PORTA_PCR19 |= PORT_PCR_PS_MASK + PORT_PCR_PE_MASK;
	GPIOA_PDDR |= GPIO_PDDR_PDD(19);//output and set output as logic 1
	GPIOA_PDOR |= GPIO_PDOR_PDO(19);	
	
	PORTB_PCR12 |= PORT_PCR_MUX(1);//GPIO output as SYNC and enable the pullup resister
	PORTB_PCR12 |= PORT_PCR_PS_MASK + PORT_PCR_PE_MASK;
	GPIOB_PDDR |= 0x1000;//GPIO_PDDR_PDD(12);//output and set output as logic 1
	GPIOB_PDOR |= 0x1000;//GPIO_PDOR_PDO(12);	
	//GPIOB_PDOR &=~ GPIO_PDOR_PDO(12);
	
	PORTB_PCR13 |= PORT_PCR_MUX(1);//GPIO output as LDAC and enable the pullup resister
	PORTB_PCR13 |= PORT_PCR_PS_MASK + PORT_PCR_PE_MASK;
	GPIOB_PDDR |= 0x2000;//output and set output as logic 1
	GPIOB_PDOR |= 0x2000;	
	
	/**
	 * PTB9 TPM0_CH2 PULSE GENERATE
	 * */
	PORTB_PCR9 |= PORT_PCR_MUX(2);//PWM TPM0_CH2
	/**
	 * PTA9 ADC0_SE2 
	 * */
	
	return 0;
}
int SPIInit()
{
	SPI0Init();
	return 0;
}

int DACInit()
{
	GPIOA_PDOR |= GPIO_PDOR_PDO(19);
	delay_n_plus_1ms(10);
	GPIOA_PDOR &=~ GPIO_PDOR_PDO(19);
	delay_n_plus_1ms(10);
	GPIOA_PDOR |= GPIO_PDOR_PDO(19);
	delay_n_plus_1ms(5);
	return 0;
}

int UARTInit()
{
#ifndef NORMALCLOCK
	UART0Init(uart0_clk_khz,TERMINAL_BAUD);
#endif
	
#ifdef NORMALCLOCK
	UART0Init_(TERMINAL_BAUD);
#endif
	return 0;
}

int PWMInit()
{
	TPM0Init(PULSECHANNEL);
	return 0;
}


int OLEDInit()
{
	
	return 0;
}


void delay(void)
{
	unsigned char i,j,k;
	
	for(k=0;k<0x40;k++)
	{
		for(i=0;i<0x80;i++)
		{
			for(j=0;j<0x80;j++)
			{
				asm("nop");
			}
		}
	}
}

void delay_n_plus_100ms(unsigned char delay_number)
{
	unsigned char i,j,k,m;
	if(0 == delay_number)
	{
		delay_number = 1;
	}
	for(m=0;m<delay_number;m++)
	{
		for(k=0;k<0x8;k++)
		{
			for(i=0;i<0x80;i++)
			{
				for(j=0;j<0x80;j++)
				{
					asm("nop");
				}
			}
		}
	}
}
void delay_n_plus_1ms(unsigned char delay_number)
{
	unsigned char i,j,k,m;
	if(0 == delay_number)
	{
		delay_number = 1;
	}
	for(m=0;m<delay_number;m++)
	{
		for(k=0;k<0x8;k++)
		{
				for(j=0;j<0x80;j++)
				{
					asm("nop");
				}
		}
	}	
}
unsigned int mathmo(int a)
{
	if(a>=0)return a;
	if(a<0)return (-a);
}
