/*Main.c*/
#include "header.h"
extern u8 h,m,s,pm;
s16 TEMP,POT,LDR;
u8 log[10];
void time_print();
void Log_Print();
void EEPROM_clr();
u8 saveCount=0,logCount=0,isrFlag=0;
int main()
{

	float Ftemp,Fpot,Fldr;
	s16 temp;
	
	u8 adr=0x00; 
	lcd_init();
	uart_init(9600);
	RTC_init();
	Ext_INT0_Init();
	EEPROM_clr();
	temp_init();
	while(1)
	{
		TEMP=i2c_device_read_temp();
		POT=Adc_Read(1);
		LDR=Adc_Read(0);
		Ftemp=TEMP;
		Fpot=POT;
		Fldr=LDR;
		lcd_cmd(0x80);
		RTC_read();
		time_print();
		lcd_cmd(0xC0);
		lcd_string("\r\nTemp : - ");
		lcd_float(Ftemp/256);
		lcd_string(" °C");
		lcd_cmd(0x94);
		lcd_string("\r\nPot : - ");
		lcd_float(Fpot*5/4096);
		lcd_cmd(0xD4);
		lcd_string("\r\nLDR : - ");
		lcd_float((Fldr/41)-1);
	
//		uart_hex(h);
//		uart_string("\r\n");
//		uart_string("\r\nTemp : - ");
//		uart_int(TEMP/256);
//		uart_string(" °C");
//		uart_string("\r\nPot : - ");
//		uart_float(POT*5/4096);	
//		uart_string("\r\nLDR : - ");
//		uart_int((LDR/41)-1);
		
		saveCount++;
		if(saveCount==5)
		{
			uart_string("Saving...\r\n");
//			log[0]=h;
//			log[1]=m;
//			log[2]=s;
//			log[3]=TEMP;
//			log[4]=TEMP>>8;
//			log[5]=LDR;
//			log[6]=LDR>>8;
//			log[7]=POT;
//			log[8]=POT>>8;
//			log[9]='\0';
			saveCount=0;
			uart_hex(adr);
	//		i2c_write_string(0xA0,logCount,log);
			logCount=logCount+1;
			uart_string("\r\n");
		//	uart_string("-------------------------\r\n");
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
		//	temp=temp>>8;
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
		//	uart_string("\r\n");
		//	uart_string("-------------------------\r\n");
			 if(logCount==10)
			 {
			 	logCount=0;
				adr=0x00;
			 }
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
	//	hour=h/16;
	//	hour=hour*10+(h%16);
		if(h > 0x12)
		{
			h1=h-0x12;	
		}
		else
		{
			h1=h;
		}
		if(h==0x00)
			h1=0x12;
	//	lcd_int(hour);
		lcd_char(h1/16+48);	//hour
		lcd_char(h1%16+48);	//hour
		lcd_char(':');
		
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
		
}

void INT0_Handler(void) interrupt 0
{
		isrFlag=1;
//		u8 dt1;
//		s16 f1,f2;
//		float Ltemp;
//		dt1=i2c_Device_Read(0xA0,0x0);
//		uart_string("Lower :- ");
//		uart_hex(dt1);
//	//	uart_tx(dt1);
//		delay_ms(10);
//		f1=dt1;
//		dt1=0;
//		dt1=i2c_Device_Read(0xA0,0x3);
//		uart_string("\r\nHigher :- ");
//		uart_hex(dt1);
//		 f2=dt1;
//		 f1|=f2<<8;
//		 Ltemp=f1;
//	//	 uart_string("\r\n*********************\r\n");
//	//	 uart_hex(f1);
//	//	 uart_string("\r\n*********************\r\n");
//		 uart_float(Ltemp/256);
//	//	uart_string("\r\n");

}
void Log_Print()
{
	u8 Logadr,cnt=0;
	u8 dt1,h1,pm;
	s16 f1,f2;
	float Ltemp;
	for(Logadr=0x00;Logadr<=100;cnt++)
	{
		dt1=i2c_Device_Read(0xA0,Logadr);
		 if(dt1 > 0x12)
			{
				h1=dt1-0x12;	
			}
			else
			{
				h1=dt1;
			}
			if(dt1==0x00)
				h1=0x12;

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
	
			pm=dt1&(1<<5);
			if(pm)
				uart_string("PM");
			else
				uart_string("AM");
			
			uart_string("      ");
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

			uart_string("      ");
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


			uart_string("      ");
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
			uart_string("\r\n");
			if(cnt==logCount)
				break;
	}

}
//void Log_Print()
//{
//		u8 h1,logAddr;
//		s16 f1,f2;
//		for(logAddr=0;logAddr<=120;logAddr=logAddr+10)
//		{
//			i2c_read_string(0xA0,logAddr,log);
//			if(log[0] > 0x12)
//			{
//				h1=log[0]-0x12;	
//			}
//			else
//			{
//				h1=log[0];
//			}
//			if(log[0]==0x00)
//				h1=0x12;
//		//	lcd_int(hour);
//			uart_tx(h1/16+48);	//hour
//			uart_tx(h1%16+48);	//hour
//			uart_tx(':');
//		
//			uart_tx(log[1]/16+48);	//minute
//			uart_tx(log[1]%16+48);	//minute
//			uart_tx(':');
//		
//			uart_tx(log[2]/16+48);	//second
//			uart_tx(log[2]%16+48);	//second
//		//	lcd_char(0x80+9);
//			pm=h&(1<<5);
//			if(pm)
//				uart_string("PM");
//			else
//				uart_string("AM");
//			
//			uart_string("      ");
//			f1=log[3];
//			f2=log[4];
//			f1|=f2<<8;
//			uart_float(f1/256);
//			uart_string("      ");
//			f1=log[5];
//			f2=log[6];
//			f1|=f2<<8;
//			uart_float((f1/41)-1);
//			uart_string("      ");
//			f1=log[7];
//			f2=log[8];
//			f1|=f2<<8;
//			uart_float(f1*5/4096);
//			uart_string("\r\n");
//			delay_ms(10);	
//		}
//}
void EEPROM_clr()
{
	u8 i=0;
	for(i=0;i<=200;i++)
	{
		i2c_Device_Write(0xA0,i,0x00);
		delay_ms(10);
	}
}