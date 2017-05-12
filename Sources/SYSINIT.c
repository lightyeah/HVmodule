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
	IOInit();
	ClockInit();
	UARTInit();
	SPIInit();
	ADCInit();
	
	/*software Initialize*/
	
	
}

int ClockInit()
{
    // releases hold with ACKISO:  Only has an effect if recovering from VLLS1, VLLS2, or VLLS3
    // if ACKISO is set you must clear ackiso before calling pll_init 
    //    or pll init hangs waiting for OSC to initialize
    // if osc enabled in low power modes - enable it first before ack
    // if I/O needs to be maintained without glitches enable outputs and modules first before ack.
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
     
     SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1); // select the FLLFLLCLK as UART0 clock source
     SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;//enable uart0 clock gate
     SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;//ENABLE SPI0 CLOCK GATE
     SIM_SCGC4 |= SIM_SCGC4_I2C0_MASK;//enable i2c clock gate
     SIM_SCGC5 |= (SIM_SCGC5_PORTA_MASK|SIM_SCGC5_PORTB_MASK);//ENABLE PORTA PORTB CLOCK GATE
    
	return 0;
}

int ADCInit()
{
	
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
	PORTB_PCR1 = PORT_PCR_MUX(2);
	PORTB_PCR2 = PORT_PCR_MUX(2);
	return 0;
}
int SPIInit()
{
	
	return 0;
}

int UARTInit()
{
	UART0Init(uart0_clk_khz,TERMINAL_BAUD);
	return 0;
}

int PWMInit()
{
	
	return 0;
}


int OLEDInit()
{
	
	return 0;
}

int DACInit()
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
