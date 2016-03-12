#include "includes.h"
#include "bmp.h"


static OS_STK startup_task_LED0[STARTUP_TASK_LED0_SIZE];
static OS_STK startup_task_LED1[STARTUP_TASK_LED1_SIZE];
static OS_STK startup_task_LED2[STARTUP_TASK_LED2_SIZE];
static OS_STK startup_task_USART[STARTUP_TASK_USART_SIZE];
static OS_STK startup_task_LCD[STARTUP_TASK_LCD_SIZE];

//extern	OS_EVENT	*USART_SEM;				 //信号量			   
extern	OS_EVENT	*USART_Q;					//消息队列
	
//**************************************************//
//***********PE 2 3  以200个节拍闪烁****************//
//**************************************************//

void Task_LED0(void *p_arg)
{
    (void)p_arg;                		// 'p_arg' 并没有用到，防止编译器提示警告    	
	while (1)
    {
        LED0( ON );
		OSTimeDlyHMSM(0, 0,0,300);
        LED0( OFF);
		OSTimeDlyHMSM(0, 0,0,300);
    }
}
//**************************************************//
//*********PE 4 5  以500个节拍闪烁*****************//
//**************************************************//
void Task_LED1(void *P_arg)
{
	P_arg=P_arg;				//	防止警告
	for(;;)
	{
	 	LED1( ON );
		OSTimeDly(700);
        LED1( OFF);
		OSTimeDly(700);
	 }
}

//**************************************************//
//***********PE 2 3  以200个节拍闪烁****************//
//**************************************************//

void Task_LED2(void *p_arg)
{
    (void)p_arg;                		// 'p_arg' 并没有用到，防止编译器提示警告    	
	while (1)
    {
        LED2( ON );
		OSTimeDlyHMSM(0, 0,1,0);
        LED2( OFF);
		OSTimeDlyHMSM(0, 0,1,0);
    }
}

//************************************************//
//***********通过串口发送数据给电脑****************//
//**************************************************//
void Task_Usart(void *P_arg)
{
	INT8U err;	
    //unsigned char *msg;
	void *msg;
	P_arg=P_arg;
	for(;;)
	{
		/*#if 0												//不用的话就注释掉
		//通过邮箱接收消息
		msg=(unsigned char *) OSMboxPend(USART_MBOX,0,&err); //等待串口接收指令成功的邮箱信息		             
	    if(err==OS_NO_ERR)	
		{
			Usart1_PutStr(msg);
			Usart1_PutStr("\r\n");
		}
		else if(err==OS_ERR_EVENT_TYPE)
			Usart1_PutStr("TYPE\r\n");
		else if(err==OS_ERR_PEVENT_NULL)
			Usart1_PutStr("NULL\r\n");
		else if(err==OS_TIMEOUT)
			Usart1_PutStr("TIMEOUT\r\n");
		else
			Usart1_PutStr("PEND_ISR\r\n");

		Usart1_PutStr("Hello,uCOS\r\n");
	   #endif*/
	   
	   /*#if 0											  //不用的话就注释掉
	   //通过信号量判断是否成功接收
	    OSSemPend(USART_SEM,0,&err);
		switch (err)
		{
			case OS_NO_ERR:			Usart1_PutStr("YES\r\n");			break;		//成功接收到信号量
			case OS_TIMEOUT:		Usart1_PutStr("TIMEOUT\r\n");		break;		//等待超时
			case OS_ERR_EVENT_TYPE:	Usart1_PutStr("Pevent is ERR\r\n");	break;		//信号量指向有错误
			case OS_ERR_PEND_ISR:	Usart1_PutStr("Not allow use it in ISR\r\n");break;//中断中不能使用
			case OS_ERR_PEVENT_NULL:Usart1_PutStr("空指针\r\n");		break;		//空指针;
			default:				Usart1_PutStr("NOT KNOW ERR\r\n");	break;	
		 }
		#endif*/
		OSTimeDly(100);
		//通过消息队列接收串口中断发来的消息
		msg=OSQPend(USART_Q, 1000, &err);
		switch (err)
		{
		 	case	OS_ERR_NONE:        Uart_SendStr(msg);
										Uart_SendStr("\r\n");						break;
			case	OS_ERR_TIMEOUT:	    Uart_SendStr("TIMEOUT\r\n");				break;
			case	OS_ERR_EVENT_TYPE:	Uart_SendStr("指针指向错误！\r\n");		break;
			case	OS_ERR_PEVENT_NULL:	Uart_SendStr("空指针！\r\n");				break;
			case	OS_ERR_PEND_ISR:	Uart_SendStr("Not allow use it in ISR!\r\n");break;
			default:					Uart_SendStr("NOT KNOW ERR\r\n");			break;
		}
	}
}
//**************************************************//
//***********lcd任务****************//
//**************************************************//

void Task_LCD(void *p_arg)
{
    unsigned int i = 0;
    char j = 0;
    (void)p_arg;                		// 'p_arg' 并没有用到，防止编译器提示警告    	

	while (1)
    {
     	LED3( ON );		
		LCD_PutString(19,190,"I LOVE MY JOB ",Red,Black);
		
		LCD_PutString(220,190,"专业开发板",0xF800,Yellow);
		LCD_PutString(250,60,"王琳斌",Black,Cyan);
		LCD_PutString(0,220,";:[]{}\|?)(-=+*&^%$",Yellow,Blue2);
		LCD_TEST_Picture1(picture1);
		OSTimeDlyHMSM(0, 0,1,1);
		LED3( OFF );
        j = i++ % 10 + 0x30;
        LCD_PutString(220,210, &j, 0xF800, Blue2);
		//OSTimeDlyHMSM(0, 0,1,0);
   
    }
}


//***************************************************//
//*********开始创建任务，完成后删除自己*************//
//*********分别用OSTaskCreate和OSTaskCreateExt创建任务***//
//*************************************************///
void Task_Star(void *P_arg)
{	
	INT8U	err;
	P_arg=P_arg;	
	
	//创建第一个任务
	OSTaskCreate(Task_LED0,				
				(void *)0,
	   			&startup_task_LED0[STARTUP_TASK_LED0_SIZE-1],
				STARTUP_TASK_LED0_PRIO);
	//创建第二个任务
	OSTaskCreateExt(Task_LED1,		   
					(void *)0,
					&startup_task_LED1[STARTUP_TASK_LED1_SIZE-1],
					STARTUP_TASK_LED1_PRIO,
					STARTUP_TASK_LED1_PRIO,	 //ID暂时未用到，可以设成跟优先级一样的数值
					&startup_task_LED1[0],
					80,
					(void *)0,
					OS_TASK_OPT_STK_CHK		//允许检查栈的使用情况
					);
	//创建第三个任务
	OSTaskCreateExt(Task_LED2,		   
					(void *)0,
					&startup_task_LED2[STARTUP_TASK_LED2_SIZE-1],
					STARTUP_TASK_LED2_PRIO,
					STARTUP_TASK_LED2_PRIO,	 //ID暂时未用到，可以设成跟优先级一样的数值
					&startup_task_LED1[0],
					80,
					(void *)0,
					OS_TASK_OPT_STK_CHK		//允许检查栈的使用情况
					);
	//创建第四个任务
	OSTaskCreateExt(Task_Usart,		   
					(void *)0,
					&startup_task_USART[STARTUP_TASK_USART_SIZE-1],
					STARTUP_TASK_USART_PRIO,
					STARTUP_TASK_USART_PRIO,	 //ID暂时未用到，可以设成跟优先级一样的数值
					&startup_task_USART[0],
					80,
					(void *)0,
					OS_TASK_OPT_STK_CHK		//允许检查栈的使用情况
					); 
	OSTaskCreate(Task_LCD,				
				(void *)0,
	   			&startup_task_LCD[STARTUP_TASK_LCD_SIZE-1],
				STARTUP_TASK_LCD_PRIO);
	
	//请求删除任务本身
	/*err=OSTaskDelReq(OS_PRIO_SELF);			 
	if(err==OS_NO_ERR)						 //如果请求已经被记录
	{
		while(err!=OS_TASK_NOT_EXIST)		 //一直等待直到删除
		{
			OSTaskDel(OS_PRIO_SELF);
			OSTimeDly(1);						
		}
		
	}*/			
	for(;;)
	{										 //无用的任务
	 	OSTimeDly(100);
	}
}
