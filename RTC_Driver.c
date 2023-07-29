/*RTC_Driver.c*/
#include "header.h"
u8 h,m,s,pm;
void RTC_init()
{
	/*set RTC time 11:59:50 pm*/
	i2c_Device_Write(0xD0,0x2,0x71); //set hour
	i2c_Device_Write(0xD0,0x1,0x59); //set minute
	i2c_Device_Write(0xD0,0x0,0x55); //set second  

}
	/*reding RTC time*/
void RTC_read()
{
	     h=i2c_Device_Read(0xD0,0x2); //read hour
	 	 m=i2c_Device_Read(0xD0,0x1); //read minute
  		 s=i2c_Device_Read(0xD0,0x0); //read second

	/*	 time[0]=h/16+48;
		 time[1]=h%16+48;
		 time[2]=':';
	     time[3]=m/16+48;
		 time[4]=m%16+48;
		 time[5]=':';
		 time[6]=s/16+48;
		 time[7]=s%16+48;
		 time[8]=' ';
		pm=h&(1<<5);
		if(pm)
			time[9]='P';
		else
			time[9]='A';
		time[10]='M';
		time[11]='/0';		   */
	}
