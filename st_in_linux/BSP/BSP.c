//*********************************************************************************/
//* 文件名  ：BSP.c
//* 描述    ：所有接口初始化，包括SysTick定时器。         
//* 实验平台：EEPW_stm32zet6开发板
//* 库版本  ：ST3.5.0+uCOS2.86
//*
//* 作者    ：wlb  
//**********************************************************************************/	

#include "includes.h"

/*
 * 函数名：SysTick_init
 * 描述  ：配置SysTick定时器
 * 输入  ：无
 * 输出  ：无
 */
void SysTick_init(void)
{//OS_TICKS_PER_SEC
    SysTick_Config(SystemCoreClock/OS_TICKS_PER_SEC);//初始化并使能SysTick定时器
}

/*
 * 函数名：BSP_Init
 * 描述  ：时钟初始化、硬件初始化
 * 输入  ：无
 * 输出  ：无
 */
void BSP_Init(void)
{
    SystemInit();				//* 配置系统时钟为72M	
    LED_GPIO_Config(); 		 	//* LED 端口初始化
	Lcd_GPIO_Config();			//*LCD的IO配置
	Lcd_FMSC_Config();			//*LCD的FMSC配置
	USART_Configuration();		//*串口初始化
	NVIC_Configuration();		//*配置中断优先级
	
	LCD_Init();					//*LCD初始化
    SysTick_init();
}

