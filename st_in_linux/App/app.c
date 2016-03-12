#include "includes.h"
#include "bmp.h"


static OS_STK startup_task_LED0[STARTUP_TASK_LED0_SIZE];
static OS_STK startup_task_LED1[STARTUP_TASK_LED1_SIZE];
static OS_STK startup_task_LED2[STARTUP_TASK_LED2_SIZE];
static OS_STK startup_task_USART[STARTUP_TASK_USART_SIZE];
static OS_STK startup_task_LCD[STARTUP_TASK_LCD_SIZE];

//extern	OS_EVENT	*USART_SEM;				 //�ź���			   
extern	OS_EVENT	*USART_Q;					//��Ϣ����
	
//**************************************************//
//***********PE 2 3  ��200��������˸****************//
//**************************************************//

void Task_LED0(void *p_arg)
{
    (void)p_arg;                		// 'p_arg' ��û���õ�����ֹ��������ʾ����    	
	while (1)
    {
        LED0( ON );
		OSTimeDlyHMSM(0, 0,0,300);
        LED0( OFF);
		OSTimeDlyHMSM(0, 0,0,300);
    }
}
//**************************************************//
//*********PE 4 5  ��500��������˸*****************//
//**************************************************//
void Task_LED1(void *P_arg)
{
	P_arg=P_arg;				//	��ֹ����
	for(;;)
	{
	 	LED1( ON );
		OSTimeDly(700);
        LED1( OFF);
		OSTimeDly(700);
	 }
}

//**************************************************//
//***********PE 2 3  ��200��������˸****************//
//**************************************************//

void Task_LED2(void *p_arg)
{
    (void)p_arg;                		// 'p_arg' ��û���õ�����ֹ��������ʾ����    	
	while (1)
    {
        LED2( ON );
		OSTimeDlyHMSM(0, 0,1,0);
        LED2( OFF);
		OSTimeDlyHMSM(0, 0,1,0);
    }
}

//************************************************//
//***********ͨ�����ڷ������ݸ�����****************//
//**************************************************//
void Task_Usart(void *P_arg)
{
	INT8U err;	
    //unsigned char *msg;
	void *msg;
	P_arg=P_arg;
	for(;;)
	{
		/*#if 0												//���õĻ���ע�͵�
		//ͨ�����������Ϣ
		msg=(unsigned char *) OSMboxPend(USART_MBOX,0,&err); //�ȴ����ڽ���ָ��ɹ���������Ϣ		             
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
	   
	   /*#if 0											  //���õĻ���ע�͵�
	   //ͨ���ź����ж��Ƿ�ɹ�����
	    OSSemPend(USART_SEM,0,&err);
		switch (err)
		{
			case OS_NO_ERR:			Usart1_PutStr("YES\r\n");			break;		//�ɹ����յ��ź���
			case OS_TIMEOUT:		Usart1_PutStr("TIMEOUT\r\n");		break;		//�ȴ���ʱ
			case OS_ERR_EVENT_TYPE:	Usart1_PutStr("Pevent is ERR\r\n");	break;		//�ź���ָ���д���
			case OS_ERR_PEND_ISR:	Usart1_PutStr("Not allow use it in ISR\r\n");break;//�ж��в���ʹ��
			case OS_ERR_PEVENT_NULL:Usart1_PutStr("��ָ��\r\n");		break;		//��ָ��;
			default:				Usart1_PutStr("NOT KNOW ERR\r\n");	break;	
		 }
		#endif*/
		OSTimeDly(100);
		//ͨ����Ϣ���н��մ����жϷ�������Ϣ
		msg=OSQPend(USART_Q, 1000, &err);
		switch (err)
		{
		 	case	OS_ERR_NONE:        Uart_SendStr(msg);
										Uart_SendStr("\r\n");						break;
			case	OS_ERR_TIMEOUT:	    Uart_SendStr("TIMEOUT\r\n");				break;
			case	OS_ERR_EVENT_TYPE:	Uart_SendStr("ָ��ָ�����\r\n");		break;
			case	OS_ERR_PEVENT_NULL:	Uart_SendStr("��ָ�룡\r\n");				break;
			case	OS_ERR_PEND_ISR:	Uart_SendStr("Not allow use it in ISR!\r\n");break;
			default:					Uart_SendStr("NOT KNOW ERR\r\n");			break;
		}
	}
}
//**************************************************//
//***********lcd����****************//
//**************************************************//

void Task_LCD(void *p_arg)
{
    unsigned int i = 0;
    char j = 0;
    (void)p_arg;                		// 'p_arg' ��û���õ�����ֹ��������ʾ����    	

	while (1)
    {
     	LED3( ON );		
		LCD_PutString(19,190,"I LOVE MY JOB ",Red,Black);
		
		LCD_PutString(220,190,"רҵ������",0xF800,Yellow);
		LCD_PutString(250,60,"���ձ�",Black,Cyan);
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
//*********��ʼ����������ɺ�ɾ���Լ�*************//
//*********�ֱ���OSTaskCreate��OSTaskCreateExt��������***//
//*************************************************///
void Task_Star(void *P_arg)
{	
	INT8U	err;
	P_arg=P_arg;	
	
	//������һ������
	OSTaskCreate(Task_LED0,				
				(void *)0,
	   			&startup_task_LED0[STARTUP_TASK_LED0_SIZE-1],
				STARTUP_TASK_LED0_PRIO);
	//�����ڶ�������
	OSTaskCreateExt(Task_LED1,		   
					(void *)0,
					&startup_task_LED1[STARTUP_TASK_LED1_SIZE-1],
					STARTUP_TASK_LED1_PRIO,
					STARTUP_TASK_LED1_PRIO,	 //ID��ʱδ�õ���������ɸ����ȼ�һ������ֵ
					&startup_task_LED1[0],
					80,
					(void *)0,
					OS_TASK_OPT_STK_CHK		//������ջ��ʹ�����
					);
	//��������������
	OSTaskCreateExt(Task_LED2,		   
					(void *)0,
					&startup_task_LED2[STARTUP_TASK_LED2_SIZE-1],
					STARTUP_TASK_LED2_PRIO,
					STARTUP_TASK_LED2_PRIO,	 //ID��ʱδ�õ���������ɸ����ȼ�һ������ֵ
					&startup_task_LED1[0],
					80,
					(void *)0,
					OS_TASK_OPT_STK_CHK		//������ջ��ʹ�����
					);
	//�������ĸ�����
	OSTaskCreateExt(Task_Usart,		   
					(void *)0,
					&startup_task_USART[STARTUP_TASK_USART_SIZE-1],
					STARTUP_TASK_USART_PRIO,
					STARTUP_TASK_USART_PRIO,	 //ID��ʱδ�õ���������ɸ����ȼ�һ������ֵ
					&startup_task_USART[0],
					80,
					(void *)0,
					OS_TASK_OPT_STK_CHK		//������ջ��ʹ�����
					); 
	OSTaskCreate(Task_LCD,				
				(void *)0,
	   			&startup_task_LCD[STARTUP_TASK_LCD_SIZE-1],
				STARTUP_TASK_LCD_PRIO);
	
	//����ɾ��������
	/*err=OSTaskDelReq(OS_PRIO_SELF);			 
	if(err==OS_NO_ERR)						 //��������Ѿ�����¼
	{
		while(err!=OS_TASK_NOT_EXIST)		 //һֱ�ȴ�ֱ��ɾ��
		{
			OSTaskDel(OS_PRIO_SELF);
			OSTimeDly(1);						
		}
		
	}*/			
	for(;;)
	{										 //���õ�����
	 	OSTimeDly(100);
	}
}
