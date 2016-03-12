//*********************************************************************************/
//* �ļ���  ��led.c
//* ����    ������LED3��LED4��LED5��LED6��         
//* ʵ��ƽ̨��EEPW_stm32zet6������
//* ��汾  ��ST3.5.0+uCOS2.86
//*
//* ����    ��wlb  
//**********************************************************************************/	

#include "led.h"

/*
 * ��������LED_GPIO_Config
 * ����  ������LED�õ���I/O��
 * ����  ����
 * ���  ����
 */
void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE, ENABLE);

  	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_SetBits(GPIOE,GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5);	 // turn off all led
}


/******************* (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� *****END OF FILE****/
