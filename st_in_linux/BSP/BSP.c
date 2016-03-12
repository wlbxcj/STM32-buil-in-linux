//*********************************************************************************/
//* �ļ���  ��BSP.c
//* ����    �����нӿڳ�ʼ��������SysTick��ʱ����         
//* ʵ��ƽ̨��EEPW_stm32zet6������
//* ��汾  ��ST3.5.0+uCOS2.86
//*
//* ����    ��wlb  
//**********************************************************************************/	

#include "includes.h"

/*
 * ��������SysTick_init
 * ����  ������SysTick��ʱ��
 * ����  ����
 * ���  ����
 */
void SysTick_init(void)
{//OS_TICKS_PER_SEC
    SysTick_Config(SystemCoreClock/OS_TICKS_PER_SEC);//��ʼ����ʹ��SysTick��ʱ��
}

/*
 * ��������BSP_Init
 * ����  ��ʱ�ӳ�ʼ����Ӳ����ʼ��
 * ����  ����
 * ���  ����
 */
void BSP_Init(void)
{
    SystemInit();				//* ����ϵͳʱ��Ϊ72M	
    LED_GPIO_Config(); 		 	//* LED �˿ڳ�ʼ��
	Lcd_GPIO_Config();			//*LCD��IO����
	Lcd_FMSC_Config();			//*LCD��FMSC����
	USART_Configuration();		//*���ڳ�ʼ��
	NVIC_Configuration();		//*�����ж����ȼ�
	
	LCD_Init();					//*LCD��ʼ��
    SysTick_init();
}

