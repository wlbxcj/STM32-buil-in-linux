#include "platform.h"

void usart_gpio_init(void)
{
	GPIO_InitTypeDef ioIt;
	
	ioIt.GPIO_Mode=GPIO_Mode_AF;
	ioIt.GPIO_OType=GPIO_OType_PP;
	ioIt.GPIO_PuPd=GPIO_PuPd_UP;
	ioIt.GPIO_Speed=GPIO_Speed_50MHz;
	ioIt.GPIO_Pin=USART_RX_PIN | USART_TX_PIN;
	
	GPIO_Init(USART_GPIO,&ioIt);
	GPIO_PinAFConfig(USART_GPIO,USART_RX_SRC,USART_GPIO_AF);
	GPIO_PinAFConfig(USART_GPIO,USART_TX_SRC,USART_GPIO_AF);
}

void usart_mode_init(void)
{
	USART_InitTypeDef uIt;
	
	uIt.USART_BaudRate=USART_BAUD;
	uIt.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	uIt.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	uIt.USART_Parity=USART_Parity_No;
	uIt.USART_StopBits=USART_StopBits_1;
	uIt.USART_WordLength=USART_WordLength_8b;
	
	USART_ClkEn();
	USART_Init(USART,&uIt);
	USART_ClearFlag(USART,USART_FLAG_RXNE);
	USART_ClearFlag(USART,USART_FLAG_TXE);
	NVIC_EnableIRQ(USART_IRQn);
	USART_ITConfig(USART,USART_IT_RXNE,ENABLE);
	
	USART_Cmd(USART,ENABLE);
}


void init(void)
{
	RCC_AHBPeriphClockCmd(0xFFFFFFFF,ENABLE);
	
	usart_gpio_init();
	usart_mode_init();
}








