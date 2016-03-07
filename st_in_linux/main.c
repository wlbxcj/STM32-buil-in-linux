#include <stdio.h>
#include <stdlib.h>

extern int __io_putchar(int);
extern char * __io_gets(char *buf,int len);

extern int __io_putchar(int);

void checkBuf(const char *buf,int len)
{
	for(int i=0;i<len;i++){
		switch(buf[i]){
			case '\n':__io_putchar('\\');__io_putchar('n');break;
			case '\0':__io_putchar('\\');__io_putchar('0');break;
			default:__io_putchar(buf[i]); break;
		}
	}
}
int main(void)
{
	char buf[20];
	__io_gets(buf,10);
	checkBuf(buf,10);
	
	return 0;
}



