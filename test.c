/*Main.c*/
#include "header.h"
extern u8 h,m,s,pm;
s16 TEMP,POT,LDR;
u8 min1,temp1;
void time_print();
void Log_Print();
void EEPROM_clr();
u8 saveCount=0,logCount=0,isrFlag=0;
int main()
{

	float Ftemp,Fpot,Fldr;
	
	u8 adr=0x00; 
	lcd_init();
	uart_init(9600);
	RTC_init();
	Ext_INT0_Init();
	uart_string("--------------------------------------------------------------------------\r\n");
	uart_string("                     Real Time Wheather Monitoring System\r\n");
	uart_string("--------------------------------------------------------------------------\r\n");
	lcd_cmd(0x80);
	lcd_string("      V19BE4D4");
	lcd_cmd(0xC0);
	lcd_string(" REAL TIME WHEATHER");
	lcd_cmd(0x94);
	min1=m/16;
	min1=min1*10+(m%16);
	temp1=min1;
	lcd_string("  MONITORING SYSTEM");
//	EEPROM_clr();
	delay_ms(3000);
//	lcd_cmd(0x01);
	temp_init();
	while(1)
	{
		TEMP=i2c_device_read_temp();
		POT=Adc_Read(1);
		LDR=Adc_Read(0);
		Ftemp=TEMP;
		Fpot=POT;
		Fldr=LDR;
		lcd_cmd(0x01);
		lcd_cmd(0x83);
		RTC_read();
		time_print();
		lcd_cmd(0xC0);
		lcd_string("\r\nTemp : ");
		lcd_float(Ftemp/256);
		lcd_string(" C");
		lcd_cmd(0x94);
		lcd_string("\r\nLight : ");
		lcd_float((Fldr/41)-1);
		lcd_string(" %");
		lcd_cmd(0xD4);
		lcd_string("\r\nPot : ");		      
		lcd_float(Fpot*5/4096);
		lcd_string(" V");
		
		//saveCount++;
		if(min1==temp1+1)
		{
			temp1=min1;
			 logCount=logCount+1;
			 if(logCount==11)
			 {
			 	logCount=1;
				adr=0x00;
			 }
		//	uart_string("Saving...");
			
			saveCount=0;
	//		uart_hex(adr);
			
		//	uart_string("\r\n");

			i2c_Device_Write(0xA0,adr,h);
			adr=adr+1;
			delay_ms(10);
			i2c_Device_Write(0xA0,adr,m);
			adr=adr+1;
			delay_ms(10);
			i2c_Device_Write(0xA0,adr,s);
			adr=adr+1;
			delay_ms(10);

			i2c_Device_Write(0xA0,adr,TEMP);
			adr=adr+1;
			delay_ms(10);
			i2c_Device_Write(0xA0,adr,TEMP>>8);
			adr=adr+1;
			delay_ms(10);

			i2c_Device_Write(0xA0,adr,LDR);
			adr=adr+1;
			delay_ms(10);
			i2c_Device_Write(0xA0,adr,LDR>>8);
			adr=adr+1;
			delay_ms(10);

			i2c_Device_Write(0xA0,adr,POT);
			adr=adr+1;
			delay_ms(10);
			i2c_Device_Write(0xA0,adr,POT>>8);
			adr=adr+1;
			delay_ms(10);
		

		}
		if(isrFlag==1)
		{
			Log_Print();
			isrFlag=0;
		}		
		delay_ms(1000);
		lcd_cmd(0x01);
	}
}
void time_print()
{
   		   	u8 h1;
	  h1=h&(0x9F);
//		if(h > 0x12)
//		{
//			h1=h-0x12;	
//		}
//		else
//		{
//			h1=h;
//		}
//		if(h==0x00)
//			h1=0x12;

		lcd_char(h1/16+48);	//hour
		lcd_char(h1%16+48);	//hour
		lcd_char(':');

		min1=m/16;
		min1=min1*10+(m%16);

		lcd_char(m/16+48);	//minute
		lcd_char(m%16+48);	//minute
		lcd_char(':');
		
		lcd_char(s/16+48);	//second
		lcd_char(s%16+48);	//second
		lcd_char(0x80+9);
			pm=h&(1<<5);
		if(pm)
			lcd_string("PM");
		else
			lcd_string("AM");

		//	lcd_int(min1);
		
}

void INT0_Handler(void) interrupt 0
{
		isrFlag=1;
}
void Log_Print()
{
	u8 Logadr,cnt=0;
	u8 dt1,h1,pm;
	s16 f1,f2;
	float Ltemp;
	uart_string("\r\n\r\n");
	uart_string("LOG ID        Time        Temperature     Light Intensity      Pot Reading\r\n");
	uart_string("--------------------------------------------------------------------------\r\n");
	for(Logadr=0x00;Logadr<=100;cnt++)
	{
		if(cnt==logCount)
				break;
		delay_ms(10);
		uart_string("   ");
		uart_int(cnt+1);
		uart_string("      ");
		dt1=i2c_Device_Read(0xA0,Logadr);
		 h1=dt1&(0x9F);
		

			uart_tx(h1/16+48);	//hour
			uart_tx(h1%16+48);	//hour
			uart_tx(':');

		
			Logadr=Logadr+1;
			delay_ms(10);
			dt1=i2c_Device_Read(0xA0,Logadr);

			uart_tx(dt1/16+48);	//minute
			uart_tx(dt1%16+48);	//minute
			uart_tx(':');

			
			Logadr=Logadr+1;
			delay_ms(10);
			dt1=i2c_Device_Read(0xA0,Logadr);
			uart_tx(dt1/16+48);	//second
			uart_tx(dt1%16+48);	//second
			Logadr=Logadr+1;
			delay_ms(10);
			pm=dt1&(1<<5);
			if(pm)
				uart_string(" PM");
			else
				uart_string(" AM");
			
			uart_string("       ");
			dt1=i2c_Device_Read(0xA0,Logadr);
			Logadr=Logadr+1;
			delay_ms(10);
			f1=dt1;
			dt1=0;
			dt1=i2c_Device_Read(0xA0,Logadr);
			Logadr=Logadr+1;
			delay_ms(10);
			f2=dt1;
			f1|=f2<<8;
			Ltemp=f1;
			uart_float(Ltemp/256);
			uart_string(" °C");

			uart_string("          ");
			dt1=i2c_Device_Read(0xA0,Logadr);
			Logadr=Logadr+1;
			delay_ms(10);
			f1=dt1;
			dt1=0;
			dt1=i2c_Device_Read(0xA0,Logadr);
			Logadr=Logadr+1;
			delay_ms(10);
			f2=dt1;
			f1|=f2<<8;
			Ltemp=f1;
			uart_float((Ltemp/41)-1);
			uart_string(" %");


			uart_string("             ");
			dt1=i2c_Device_Read(0xA0,Logadr);
			Logadr=Logadr+1;
			delay_ms(10);
			f1=dt1;
			dt1=0;
			dt1=i2c_Device_Read(0xA0,Logadr);
			Logadr=Logadr+1;
			delay_ms(10);
			f2=dt1;
			f1|=f2<<8;
			Ltemp=f1;
			uart_float(Ltemp*5/4096);
			uart_string(" V\r\n");
	
	}

}

void EEPROM_clr()
{
	u8 i=0;
	for(i=0;i<=200;i++)
	{
		i2c_Device_Write(0xA0,i,0x00);
		delay_ms(10);
	}
}
