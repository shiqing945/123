#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"	 
#include "OLED.h"
#include "string.h" 	
#include "adxl345.h"

/*****************辰哥单片机设计******************
											STM32
 * 项目			:	ADXL345加速度传感器实验                   
 * 版本			: V1.0
 * 日期			: 2024.8.15
 * MCU			:	STM32F103C8T6
 * 接口			:	见adxl345.h							
 * BILIBILI	:	辰哥单片机设计
 * CSDN			:	辰哥单片机设计
 * 作者			:	辰哥

**********************BEGIN***********************/

float x_angle,y_angle,z_angle;

int main(void)
{	
	unsigned char p[16]=" ";

	short temperature = 0; 				//温度值
	delay_init(72);	  
  LED_Init();		  				//初始化与控制设备连接的硬件接口
	OLED_Init();					//OLED初始化
	delay_ms(50);
	OLED_Clear();						//清屏
	//显示“角度：”
	OLED_ShowChinese(0,0,0,16,1);
	OLED_ShowChinese(16,0,1,16,1);
	OLED_ShowChar(40,0,':',16,1);
	OLED_ShowChar(25,20,'X',16,1);
	OLED_ShowChar(62,20,'Y',16,1);
	OLED_ShowChar(100,20,'Z',16,1);
	ADXL345_Init();	

	delay_ms(1000);
	USART1_Config();//串口初始化
	
 	while(1)
	{	
			get_angle(&x_angle,&y_angle,&z_angle);
		
			printf("      %2.1f  %2.1f  %2.1f \n ",x_angle,y_angle,z_angle);
			sprintf((char*)p,"%4.1f  ",(float)x_angle);
			OLED_ShowString(0,40,p ,16,1);
		
			sprintf((char*)p,"%4.1f  ",(float)y_angle);
			OLED_ShowString(40,40,p ,16,1);
		
			sprintf((char*)p,"%4.1f  ",(float)z_angle);
			OLED_ShowString(90,40,p ,16,1);
		
//			OLED_ShowChar(60,16,temperature/100+'0',16,1);
//			OLED_ShowChar(68,16,temperature%100/10+'0',16,1);
//			OLED_ShowChar(76,16,'.',16,1);
//			OLED_ShowChar(84,16,temperature%10+'0',16,1);
		
			delay_ms(100);
	}	
}
