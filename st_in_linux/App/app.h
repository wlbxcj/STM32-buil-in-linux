#ifndef	_APP_H_
#define	_APP_H_



/**************** 用户任务声明 *******************/
void Task_Star(void *P_arg);

void Task_LED0(void *p_arg);				//任务1
void Task_LED1(void *P_arg);				//任务2	
void Task_LED2(void *P_arg);
void Task_USART(void *P_arg);
void Task_LCD(void *P_arg);

#endif	//_APP_H_
