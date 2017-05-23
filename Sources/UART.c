/*
 * UART.c
 *
 *  Created on: May 11, 2017
 *      Author: luoyang
 */

#include "common.h"

#define COMMANDHEAD01    'L'//0x4c
#define COMMANDHEAD02    'M'//0x4d
#define COMMANDADRHV     'J'//0x4a
#define COMMANDADRDEB    'K'//0x4b
#define COMMANDEND       'Z'//0x5a


    uint32 calculated_baud = 0;
    uint32 baud_diff = 0;
    uint32 osr_val = 0;
    uint32 sbr_val, uart0clk;
    uint32 baud_rate;
    uint32 reg_temp = 0;
    uint32 temp = 0;
    
    extern hvtype HV_Set;
    extern hvtype HV_Real;
    extern hvtype HV_Target;
    hvtype Temp_HV_Target;
    hvtype Temp_HV_Real;
    
    /**状态机解读串口命令
     * 
     * */
    enum UARTSTATE{
    	IDLE,
    	HEAD,
    	ADR,
    	DATA,
    	DATA01,
    	DATA02,
    	DATAE,
    	END,
    	CHECK,
    	DONE
    }CommandState = IDLE;
    
    char CommandAddress = 0;//命令地址位
    char CheckCode = 0;//加和校验
    
    
    /*
     * Initialize the uart0 for 8N1 operation, interrupts disabled, and
     * no hardware flow-control
     *
     * NOTE: Since the uarts are pinned out in multiple locations on most
     *       Kinetis devices, this driver does not enable uart pin functions.
     *       The desired pins should be enabled before calling this init function.
     *
     * Parameters:
     *  sysclk      uart module Clock in kHz(used to calculate baud)
     *  baud        uart baud rate
     */    
#ifndef NORMALCLOCK

void UART0Init(int sysclk, int baud)
{
    uint8 i;

    // Disable UART0 before changing registers
    UART0_C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK);
    
    UART0_C2 |= UART0_C2_RIE_MASK;//ENABLE RECEIVER INTERRUPT FOR RDRF
    // Verify that a valid clock value has been passed to the function 
    if ((sysclk > 50000) || (sysclk < 32))
    {
        sysclk = 0;
        reg_temp = SIM_SOPT2;
        reg_temp &= ~SIM_SOPT2_UART0SRC_MASK;
        reg_temp |= SIM_SOPT2_UART0SRC(0);
        SIM_SOPT2 = reg_temp;
			
			  // Enter inifinite loop because the 
			  // the desired system clock value is 
			  // invalid!!
			  while(1)
				{}
    }
    
    // Verify that a valid value has been passed to TERM_PORT_NUM and update
    // uart0_clk_hz accordingly.  Write 0 to TERM_PORT_NUM if an invalid 
    // value has been passed.  
    if (TERM_PORT_NUM != 0)
    {
        reg_temp = SIM_SOPT2;
        reg_temp &= ~SIM_SOPT2_UART0SRC_MASK;
        reg_temp |= SIM_SOPT2_UART0SRC(0);
        SIM_SOPT2 = reg_temp;
			
			  // Enter inifinite loop because the 
			  // the desired terminal port number 
			  // invalid!!
			  while(1)
				{}
    }
    
    // Initialize baud rate
    baud_rate = baud;
    
    // Change units to Hz
    uart0clk = sysclk * 1000 * 4;	//xuetao added plus 4
    // Calculate the first baud rate using the lowest OSR value possible.  
    i = 4;
    sbr_val = (uint32)(uart0clk/(baud_rate * i));
    calculated_baud = (uart0clk / (i * sbr_val));
        
    if (calculated_baud > baud_rate)
        baud_diff = calculated_baud - baud_rate;
    else
        baud_diff = baud_rate - calculated_baud;
    
    osr_val = i;
        
    // Select the best OSR value
    for (i = 5; i <= 32; i++)
    {
        sbr_val = (uint32)(uart0clk/(baud_rate * i));
        calculated_baud = (uart0clk / (i * sbr_val));
        
        if (calculated_baud > baud_rate)
            temp = calculated_baud - baud_rate;
        else
            temp = baud_rate - calculated_baud;
        
        if (temp <= baud_diff)
        {
            baud_diff = temp;
            osr_val = i; 
        }
    }
    
    if (baud_diff < ((baud_rate / 100) * 3))
    {
        // If the OSR is between 4x and 8x then both
        // edge sampling MUST be turned on.  
        if ((osr_val >3) && (osr_val < 9))
            UART0_C5|= UART0_C5_BOTHEDGE_MASK;
        
        // Setup OSR value 
        reg_temp = UART0_C4;
        reg_temp &= ~UART0_C4_OSR_MASK;
        reg_temp |= UART0_C4_OSR(osr_val-1);
    
        // Write reg_temp to C4 register
        UART0_C4 = reg_temp;
        
        reg_temp = (reg_temp & UART0_C4_OSR_MASK) + 1;
        sbr_val = (uint32)((uart0clk)/(baud_rate * (reg_temp)));
        
         /* Save off the current value of the uartx_BDH except for the SBR field */
        reg_temp = UART0_BDH & ~(UART0_BDH_SBR(0x1F));
   
        UART0_BDH = reg_temp |  UART0_BDH_SBR(((sbr_val & 0x1F00) >> 8));
        UART0_BDL = (uint8)(sbr_val & UART0_BDL_SBR_MASK);
        
        /* Enable receiver and transmitter */
        UART0_C2 |= (UART0_C2_TE_MASK
                    | UART0_C2_RE_MASK );
    }
    else
		{
        // Unacceptable baud rate difference
        // More than 3% difference!!
        // Enter infinite loop!
        while(1)
				{}
		}					
    
}
#endif

#ifdef NORMALCLOCK

void UART0Init_(int baud)
{
	int i = 0;
	// Disable UART0 before changing registers
	UART0_C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK);
	 /*   
	UART0_BDH |= 0x00;
	UART0_BDL |= 0x8F;
	UART0_C4 |= 0x0F;//baud rate 9600*/
    baud_rate = baud;
    
    // Change units to Hz
    uart0clk = NORMALCLOCK;//
    // Calculate the first baud rate using the lowest OSR value possible.  
    i = 4;
    sbr_val = (uint32)(uart0clk/(baud_rate * i));
    calculated_baud = (uart0clk / (i * sbr_val));
        
    if (calculated_baud > baud_rate)
        baud_diff = calculated_baud - baud_rate;
    else
        baud_diff = baud_rate - calculated_baud;
    
    osr_val = i;
        
    // Select the best OSR value
    for (i = 5; i <= 32; i++)
    {
        sbr_val = (uint32)(uart0clk/(baud_rate * i));
        calculated_baud = (uart0clk / (i * sbr_val));
        
        if (calculated_baud > baud_rate)
            temp = calculated_baud - baud_rate;
        else
            temp = baud_rate - calculated_baud;
        
        if (temp <= baud_diff)
        {
            baud_diff = temp;
            osr_val = i; 
        }
    }
    
    if (baud_diff < ((baud_rate / 100) * 3))
    {
        // If the OSR is between 4x and 8x then both
        // edge sampling MUST be turned on.  
        if ((osr_val >3) && (osr_val < 9))
            UART0_C5|= UART0_C5_BOTHEDGE_MASK;
        
        // Setup OSR value 
        reg_temp = UART0_C4;
        reg_temp &= ~UART0_C4_OSR_MASK;
        reg_temp |= UART0_C4_OSR(osr_val-1);
    
        // Write reg_temp to C4 register
        UART0_C4 = reg_temp;
        
        reg_temp = (reg_temp & UART0_C4_OSR_MASK) + 1;
        sbr_val = (uint32)((uart0clk)/(baud_rate * (reg_temp)));
        
         /* Save off the current value of the uartx_BDH except for the SBR field */
        reg_temp = UART0_BDH & ~(UART0_BDH_SBR(0x1F));
   
        UART0_BDH = reg_temp |  UART0_BDH_SBR(((sbr_val & 0x1F00) >> 8));
        UART0_BDL = (uint8)(sbr_val & UART0_BDL_SBR_MASK);
        
        /* Enable receiver and transmitter */
        UART0_C2 |= (UART0_C2_TE_MASK
                    | UART0_C2_RE_MASK );
    }
	
	UART0_C2 |= UART0_C2_RIE_MASK;//ENABLE RECEIVER INTERRUPT FOR RDRF
	
	UART0_C2 |= (UART0_C2_TE_MASK|UART0_C2_RE_MASK);
	
}

#endif
/********************************************************************/
/*
 * Wait for a character to be received on the specified uart
 *
 * Parameters:
 *  channel      uart channel to read from
 *
 * Return Values:
 *  the received character
 */
char UART0GetChar ()
{
      /* Wait until character has been received */
      while (!(UART0_S1 & UART0_S1_RDRF_MASK));
    
      /* Return the 8-bit data from the receiver */
      return UART0_D;
}
/********************************************************************/
/*
 * Wait for space in the uart Tx FIFO and then send a character
 *
 * Parameters:
 *  channel      uart channel to send to
 *  ch			 character to send
 */ 
void UART0SendChar (char ch)
{
      /* Wait until space is available in the FIFO */
      while(!(UART0_S1 & UART0_S1_TDRE_MASK));
    
      /* Send the character */
      UART0_D = (uint8)ch;
    
 }
/********************************************************************/
/*
 * Check to see if a character has been received
 *
 * Parameters:
 *  channel      uart channel to check for a character
 *
 * Return values:
 *  0       No character received
 *  1       Character has been received
 */
int UART0GetCharPresent (UART0_MemMapPtr channel)
{
    return (UART0_S1 & UART0_S1_RDRF_MASK);
}
/********************************************************************/
/**
 * 类似16进制转换 
 * example: dtoa(char c = 14) = D
 */
unsigned char dtoa(unsigned char n) 
{
   return (n>=10)? (n+'A'-10):(n+'0');
}

void UART0SendHex(unsigned char data)
{
 	UART0SendChar(dtoa((data&0xF0)>>4));
 	UART0SendChar(dtoa((data&0x0F)));
}

void UART0SendString(char * str) 
{
  	while((*str)!=0) 
	{
    		UART0SendChar(*str);
    		str++;
  	}
}

unsigned int Char2Num(unsigned char ch)
{ 
      /* if(( ch <= '9') && (ch >= '0')) 
		return(ch-'0');
       else if (( ch <= 'F') && (ch >= 'A')) 
		return(ch-'A'+10);
       else  return(0);*/
	
	unsigned int temp = 0;
	temp = ((ch&0xff)>>4)*10 + (ch&0x0f);
	return temp;
}

unsigned int TermGetNum(void)
 {
   unsigned int temp=0;
   unsigned char ch=0;  
   while(  (ch = UART0GetChar(UART0_BASE_PTR)) != 0x0D)
   { 
      temp = temp*10 + Char2Num(ch);
      UART0SendChar(ch); 
      //send back to terminal if needed
   }
   return(temp);  
}

void UART0_IRQHandler(void)
{
	char R_Data;
	while(!(UART0_S1 & UART0_S1_RDRF_MASK));
	R_Data = UART0_D;
	//UART0SendChar(R_Data&0xff);
	if(CommandState!=CHECK)
	{
		switch(R_Data)
		{
		case COMMANDHEAD01://帧头 L 0x4c
			//UART0SendChar(COMMANDHEAD01);
			if(CommandState == IDLE)
			{
				CommandState = HEAD;
			}
			else
			{
				CommandState = HEAD;
			}
			CheckCode = R_Data;
			//UART0SendChar(CheckCode);
			break;
		case COMMANDHEAD02://帧头 M 0x4D
			//UART0SendChar(COMMANDHEAD02);
			if(CommandState == HEAD)
			{
				CheckCode += R_Data;
				//UART0SendChar(CheckCode);
				CommandState = ADR;
				break;
			}
			else
			{
				CommandState = IDLE;
				CheckCode = 0;
			}		
			break;
		case COMMANDADRHV://命令J 高压模式 0x4A
			//UART0SendChar(COMMANDADRHV);
			if(CommandState == ADR)
			{
				CommandState = DATA;
				CheckCode += R_Data;
				//UART0SendChar(CheckCode);
				CommandAddress = COMMANDADRHV;
			}
			else
			{
				CommandState = IDLE;
				CheckCode = 0;
			}
			break;
		case COMMANDADRDEB://命令 K  调试模式 0x4B
			if(CommandState == ADR)
			{
				CommandState = DATA;
				CheckCode += R_Data;
				//UART0SendChar(CheckCode);
				CommandAddress = COMMANDADRDEB;
			}
			else
			{
				CommandState = IDLE;
				CheckCode = 0;
			}
			break;
		case COMMANDEND://命令Z 指令结束 0x5a
			//UART0SendChar(COMMANDEND);
			if(CommandState == DATAE)//指令数据接收完成
			{
				CommandState = END;
				CheckCode += R_Data;
				//UART0SendChar(CheckCode);
			}
			else
			{
				CommandState = IDLE;
				CheckCode = 0;
			}
			break;		
		default:
			break;
		}
		
	}
	switch(CommandState)//指令数据接收
	{
	case DATA:
		CommandState = DATA01;
		break;
	case DATA01:       
		CommandState = DATA02;                       
		//UART0SendChar(R_Data);
		CheckCode += R_Data;
		//UART0SendChar(CheckCode);
		CommandGetData(CommandAddress,R_Data,(int)DATA01);
		break;
	case DATA02:
		CommandState = DATAE;
		CheckCode += R_Data;
		//UART0SendChar(CheckCode);
		CommandGetData(CommandAddress,R_Data,(int)DATA02);
		break;
	case END:
		CommandState = CHECK;
		break;
	case CHECK:
		//UART0SendChar('D');
		if((CheckCode & 0xff)== R_Data)
		{
			CommandState = DONE;
			UARTCommandOutput();
			CommandState = IDLE;
		}
		break;
	default:
		break;
	}
}

void CommandGetData(char commandaddress, char data, int dataaddress)
{
	switch(commandaddress)
	{
	case COMMANDADRHV:
		if(dataaddress==(int)DATA01)
		{
			Temp_HV_Target = (hvtype)Char2Num(data)*100;
		}
		if(dataaddress==(int)DATA02)
		{
			Temp_HV_Target += (hvtype)Char2Num(data);
		}
		break;
	case COMMANDADRDEB:
		if(dataaddress==(int)DATA01)
		{
			Temp_HV_Real = (hvtype)Char2Num(data)*100;
		}
		if(dataaddress==(int)DATA02)
		{
			Temp_HV_Real += (hvtype)Char2Num(data);
		}
		break;
	default:
		break;
	}
}

void UARTCommandOutput()
{
	/*UART0SendString((unsigned char*)"done\r\n");
	char str[10];
	sprintf(str,"hv %d",HV_Target);
	UART0SendString(str);*/
	HV_Target = Temp_HV_Target;
	HV_Real = Temp_HV_Real;
	char str[50];
	sprintf(str,"uart hv*10 s%d t%d r%d\n",(int)(HV_Set*10),(int)(HV_Target*10),(int)(HV_Real*10));
	UART0SendString(str);
	
	
}
