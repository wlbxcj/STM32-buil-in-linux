#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__


/*******************�����������ȼ�*******************/
#define STARTUP_TASK_SART_PRIO		8	

#define STARTUP_TASK_LED0_PRIO		7	   
#define STARTUP_TASK_LED1_PRIO		6
#define STARTUP_TASK_LED2_PRIO		5
#define STARTUP_TASK_USART_PRIO		4
#define STARTUP_TASK_LCD_PRIO		3 

/************����ջ��С����λΪ OS_STK ��************/
#define STARTUP_TASK_START_SIZE   	40

#define STARTUP_TASK_LED0_SIZE   	40   
#define STARTUP_TASK_LED1_SIZE   	40
#define STARTUP_TASK_LED2_SIZE   	40
#define STARTUP_TASK_USART_SIZE   	80
#define STARTUP_TASK_LCD_SIZE   	80

#endif

