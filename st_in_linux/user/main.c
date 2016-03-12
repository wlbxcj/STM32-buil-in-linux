#include <stdio.h>
#include <stdlib.h>
#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "uart.h"
#include "led.h"
#include "includes.h"

extern volatile u32 sys_num;					//全局变量，延时时使用
OS_EVENT	*USART_Q;										//消息队列 

static OS_STK startup_task_stk[STARTUP_TASK_START_SIZE-1];	//定义栈

void delay_ms(u32 t)
{
	sys_num = t;	
	while(sys_num != 0);
}

void SysTick_Configuration(void)
{
	
	if(SysTick_Config(SystemCoreClock/1000))
	{
		while(1);
	}
	//NVIC_SetPriority(SysTick_IRQn, 0x0);

}
/*
__attribute__ ((weak))
int main(void)
{
	char buf[20];

    SystemInit();
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|
                            RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_AFIO, ENABLE);
    SysTick_Configuration();
    USART_Configuration();
    NVIC_Configuration();
    LED_Init();
	Uart_SendStr((unsigned char *)"123");
    while(1)
	{
        Uart_SendStr("hello the world!\r\n");
		//LED_Switch(GPIO_Pin_2|GPIO_Pin_3, 0);//set GPIOC.0=1 
		//LED_Switch(GPIO_Pin_4|GPIO_Pin_5, 0);//set GPIOC.0=0delay_ms(0xffff);
		GPIO_ResetBits(GPIOE, GPIO_Pin_2|GPIO_Pin_3);//set GPIOC.0=1 
		GPIO_SetBits(GPIOE,GPIO_Pin_4|GPIO_Pin_5);//set GPIOC.0=0delay_ms(0xffff);
        delay_ms(1000);
		GPIO_ResetBits(GPIOE,GPIO_Pin_4|GPIO_Pin_5);
	  	GPIO_SetBits(GPIOE,GPIO_Pin_2|GPIO_Pin_3);//set GPIOC.0=0
        delay_ms(1000);
    }
	return 0;
}
*/
int main(void)
{
	void *MyUsartMsg[10];									//存放消息数组
	
	OSInit();
	BSP_Init();
    USART_Configuration();
    NVIC_Configuration();
	Uart_SendStr((unsigned char *)"123\n");
	//USART_MBOX=OSMboxCreate((void *)0);				  	//建立消息邮箱
	//USART_SEM=OSSemCreate(0);								//建立信号量
	USART_Q=OSQCreate(&MyUsartMsg[0],10);					//建立消息队列

	OSTaskCreate(Task_Star,
				(void *)0,
	   			&startup_task_stk[STARTUP_TASK_START_SIZE-1],
				STARTUP_TASK_SART_PRIO);								 

	OSStart();
    return 0;
 }


