/*******************************************************************************
 * Copyright (C) 2006 ViewAt Technology Co., LTD.
 * All rights reserved.
 *******************************************************************************
 *
 * �ļ�����: uart.c
 *
 * �ļ�����: ��������
 * ��    ��: WLB
 * ����ʱ��: 2016-3-7
 * �ļ��汾: 
 * �޸���ʷ: 
 *           1. 2016-3-7  WLB  Created
 *******************************************************************************/

/*******************************************************************************
 *                                  ͷ�ļ�����                                 *
 *******************************************************************************/
#include "stm32f10x_conf.h"
#include "uart.h"

/*******************************************************************************
 *                          ���ļ������ȫ�ֱ����ͺ�������                     *
 *******************************************************************************/
void USART_Configuration(void)
{
    USART_InitTypeDef   USART_InitStructure;
    GPIO_InitTypeDef    GPIO_InitStructure; 

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);   //��1?����??��1����?��       ???������?��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    //RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE); //��1?����??��2����?��       �̨�?������?��
    //RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE); //��1?����??��3����?��       �̨�?������?��
    //????USART1 RX �ꡧPA.10��??a????��?��?
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    //????USART1 RX �ꡧPA.9��??a?�䨮?��?������?3?
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    //******************************************************************************
    // ��??��12?��y3?��??��?����?2?��?,��??��12?��y?a38400 ��? 8 ��?1 ��?N  ?����??D??��?��?
    //******************************************************************************
    USART_InitStructure.USART_BaudRate=115200;                        //����?����?��??��?��
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;     //��?��?��y?Y??��y
    USART_InitStructure.USART_StopBits = USART_StopBits_1;          //����?������?1????��y  
    USART_InitStructure.USART_Parity = USART_Parity_No;             //2?��??��?��??
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
                                                                 //2?��?���¨�?????
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //��1��?����?��o��?����????��
    USART_Init(USART1,&USART_InitStructure);                        //3?��??����??��1
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                  //��1?����??��1?����??D??
    USART_Cmd(USART1,ENABLE);                                       //��1?����??��1
 
}
     
void NVIC_Configuration(void)
{
    NVIC_InitTypeDef    NVIC_InitStructure;

    //NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);               
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);    //?��??��??��??2??��?�䨮��??��??2??
    //��1?����??��1?D??
    NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&NVIC_InitStructure); 
}
void Uart_SendStr(unsigned char *ph)
{   
    while(*ph!='\0')
    {
        USART_SendData(USART1,*ph);
        while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);   //�̨���y��y?Y����?��������?
        ph++;
    }
}


/*******************************************************************************
 *                             �ⲿ�����ͺ�������                              *
 *******************************************************************************/


/*******************************************************************************
 *                                End of File                                  *
 *******************************************************************************/

