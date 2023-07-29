/*LCD_Driver.c*/

#include"header.h"

sbit RS = P3^4;
sbit RW = P3^5;
sbit EN = P3^6;
#define lcd_port P2
void lcd_cmd(u8 cmd)
{
		lcd_port=cmd;
		RS=0;
		RW=0;
		EN=1;
		delay_ms(2);
		EN=0;
		delay_ms(5);	
}

void lcd_init()
{
	delay_ms(20);						
	lcd_cmd(0x38);						
	lcd_cmd(0x0C);							
	lcd_cmd(0x06);						
	lcd_cmd(0x01);							
	lcd_cmd(0x80);	
}

void lcd_char(u8 ch)
{
		lcd_port=ch;
		RS=1;
		RW=0;
		EN=1;
		delay_ms(2);
		EN=0;
		delay_ms(5);	
}

void lcd_int(s16 n)
{
	int c=0,num=0,i;
	if(n==0)
		lcd_char('0');
	if(n<0)
	{
		lcd_char('-');
		i=-n;
	}
	else
		i=n;
	for(c=0;i;i=i/10)
	{
		 num=num*10+(i%10);
		 c++;
	}
	for(i=num;i;i=i/10)
	{
		lcd_char((i%10)+48);
		c--;
	}
	while(c)
	{
		c--;
		lcd_char('0');
	}
}

void lcd_float(s32_f n)
{
	int n1;
	float n2;
	n1=n;
	n2=n-n1;
	n2=n2*100;
	if(n2<0)
		n2=-n2;
	
	lcd_int(n1);
	lcd_char('.');
	if(n2<10)
		lcd_char('0');
	lcd_int(n2);
}



void lcd_string(char *str)
{
	u8 i=0;
	while(str[i])
	{
		lcd_char(str[i]);
		i++;
	}
}
