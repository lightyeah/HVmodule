/*
 * main implementation: use this 'C' sample to create your own application
 *
 */





#include "common.h" /* include peripheral declarations */

void HVControl();
void UIControl();
void PulseControl();


hvtype HV_Set = 0.0 ;
hvtype HV_Real = 0.0;
hvtype HV_Target = 0.0;
hvtype HV_Diff[2];//目标值与真实值之间的差值 0是目前差值 1是上一次差值
float HV_P = 0.6;//PID调节 P

int main(void)
 {
	SystemInit();
	UART0SendString((unsigned char*)"helloworld\r\n");
	//NanoDACWrite(0b0011,0b0001,0xaaaa);
	//NanoDACSetVoltage(VOUTA,4.1111);
	//NanoDACWrite(0b0011,0b0001,0xd27b);
	for(;;) {	
		
	   	/*application*/
		//HVControl();
		delay_n_plus_1ms(2);
        UIControl();
        PulseControl();
		
	}
	
	return 0;
}

/**
 * application HVcontrol
 * related parameter: HV_Set       calculate by Real and Target with PID logic
 *                    HV_Real      get from adc
 *                    HV_Target    get from uart-command
 *                    
 * */
void HVControl()
{
	/**
	 * protect HV module
	 * */
	char str[30];
	sprintf(str,"hv*10 s%d t%d r%d\n",(int)(HV_Set*10),(int)(HV_Target*10),(int)(HV_Real*10));
	delay_n_plus_100ms(5);
	UART0SendString(str);
	if(HV_Target>=HVMAX)HV_Target = HVMAX;
	if(HV_Real >= HVERROR)
	{
		HV_Set = 0;
		delay_n_plus_100ms(5);
		return;
	}
	if(mathmo(HV_Real-HV_Set)>HVDEVIATION)//真实电压还没有达到设置电压误差范围内
	{
	    
		delay_n_plus_100ms(5);
		return;
	}
	if(mathmo(HV_Real-HV_Set)<HVDEVIATION)
	{
		if(HV_Target >= HV_Real)
		{
			HV_Diff[1]=HV_Diff[0];
			HV_Diff[0]=HV_Target-HV_Real;
			if(HV_Diff[0]>100)
				HV_Set+=100;
			if(HV_Diff[0]<=100)
				HV_Set+=HV_P*HV_Diff[0];
		}
		if(HV_Target < HV_Real)
		{
			HV_Diff[1]=HV_Diff[0];
			HV_Diff[0]=HV_Real-HV_Target;
			if(HV_Diff[0]>100)
				HV_Set-=100;
			if(HV_Diff[0]<=100)
				HV_Set-=HV_P*HV_Diff[0];
		}
		return;
	}	
	
}
/**
 * 
 * */
void UIControl()
{
	
}

void PulseControl()
{
	
}
