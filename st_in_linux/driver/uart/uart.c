/*******************************************************************************
 * Copyright (C) 2006 ViewAt Technology Co., LTD.
 * All rights reserved.
 *******************************************************************************
 *
 * 文件名称: uart.c
 *
 * 文件描述: 串口驱动
 * 作    者: WLB
 * 创建时间: 2016-3-7
 * 文件版本: 
 * 修改历史: 
 *           1. 2016-3-7  WLB  Created
 *******************************************************************************/

/*******************************************************************************
 *                                  头文件包含                                 *
 *******************************************************************************/
#include "stm32f10x_conf.h"
#include "uart.h"

/*******************************************************************************
 *                          本文件定义的全局变量和函数声明                     *
 *******************************************************************************/
void USART_Configuration(void)
{
    USART_InitTypeDef   USART_InitStructure;
    GPIO_InitTypeDef    GPIO_InitStructure; 

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);   //ê1?ü′??ú1ê±?ó       ???ùê±?ó
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    //RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE); //ê1?ü′??ú2ê±?ó       μí?ùê±?ó
    //RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE); //ê1?ü′??ú3ê±?ó       μí?ùê±?ó
    //????USART1 RX ￡¨PA.10￡??a????ê?è?
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    //????USART1 RX ￡¨PA.9￡??a?′ó?í?íìê?3?
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    //******************************************************************************
    // ′??ú12?êy3?ê??ˉ?¨ò?2?·?,′??ú12?êy?a38400 ￡? 8 ￡?1 ￡?N  ?óê??D??·?ê?
    //******************************************************************************
    USART_InitStructure.USART_BaudRate=115200;                        //éè?¨′?ê??ù?ê
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;     //′?ê?êy?Y??êy
    USART_InitStructure.USART_StopBits = USART_StopBits_1;          //éè?¨í￡?1????êy  
    USART_InitStructure.USART_Parity = USART_Parity_No;             //2?ó??ì?é??
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
                                                                 //2?ó?á÷á?????
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //ê1ó?·￠?íoí?óê????ú
    USART_Init(USART1,&USART_InitStructure);                        //3?ê??ˉ′??ú1
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                  //ê1?ü′??ú1?óê??D??
    USART_Cmd(USART1,ENABLE);                                       //ê1?ü′??ú1
 
}
     
void NVIC_Configuration(void)
{
    NVIC_InitTypeDef    NVIC_InitStructure;

    //NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);               
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);    //?è??ó??è??2??￡?′óó??è??2??
    //ê1?ü′??ú1?D??
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
        while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);   //μè′yêy?Y·￠?ííê±?
        ph++;
    }
}


/*******************************************************************************
 *                             外部变量和函数声明                              *
 *******************************************************************************/


/*******************************************************************************
 *                                End of File                                  *
 *******************************************************************************/

