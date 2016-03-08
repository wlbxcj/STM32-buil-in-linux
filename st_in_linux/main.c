#include <stdio.h>
#include <stdlib.h>
#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "uart.h"

int main(void)
{
	char buf[20];

    SystemInit();
    USART_Configuration();
    NVIC_Configuration();

	Uart_SendStr((unsigned char *)"123");
	return 0;
}



