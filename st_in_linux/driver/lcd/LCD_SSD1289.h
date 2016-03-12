#ifndef __LCD_SSD1289_H__
#define	__LCD_SSD1289_H__
#include	"stm32f10x_fsmc.h"

/* LCD color */
#define White          0xFFFF
#define Black          0x0000
#define Grey           0xF7DE
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0


void Lcd_GPIO_Config(void);				//IO�ڳ�ʼ��
void Lcd_FMSC_Config(void);				//�趨FMSC
void LCD_WR_ADD(u16 index);				//д��ַ
void LCD_WR_DATA(u16 val);				//д����
void LCD_WR_CMD(u16 index, u16 val);	//д���ݸ���ַ
void LCD_Set_Ver(unsigned char ver);	//���ú�����������
void LCD_Init(void);					//LCD��ʼ������
void LCD_SetPos(u16 x0,u16 y0);			//������ʾλ��
void LCD_PutString(u16 x, u16 y, u8 *s, u16 fColor, u16 bColor);  	//����Ļ����ʾ��Ӧ����
void LCD_PutChar(u16 x, u16 y, char c, u16 fColor, u16 bColor);   	//����Ļ����ʾ�ַ�����
void LCD_PutChar8x16(u16 x, u16 y, char c, u16 fColor, u16 bColor);	//����Ļ����ʾ�ַ�����
void LCD_PutGB1616(u16 x, u16  y, u8 c[2], u16 fColor,u16 bColor);	//����Ļ����ʾ����
void LCD_TEST_Picture1(unsigned char const *picture1);				//��ʾͼƬ

#endif
