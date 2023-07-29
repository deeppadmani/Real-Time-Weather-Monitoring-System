/*I2C_DRIVER.c*/
#include "header.h"
#include<intrins.h>
sbit SDA=P1^6; 	//p2.0 pin for SDA line
sbit SCL=P1^7; 	//p2.1 pin for SCL line

/*--I2C START CONDITION--*/
 void i2c_start()
 {
	 SCL=1; 	//ideal condition
	 SDA=1; 	//ideal condition
	 SDA=0; 	//start condition
 }
 
 /*--I2C STOP CONDITION--*/
 void i2c_stop()
 {
	 SCL=0;
	 SDA=0;
	 SCL=1; 	//ideal condition
	 SDA=1; 	//ideal condition
 }
 
 /*--I2C WRITE CONDITION--*/
 void  i2c_write(u8 info)
 {
	 s8 i;
	 for(i=7;i>=0;i--)
	 {
		 SCL=0;
		 SDA=(info &(1<<i))? 1 : 0;
		 SCL=1;
	 }
 }
 
 /*--I2C READ CONDITION--*/
 u8 i2c_read()
 {
	 u8 temp=0x0;
	 s8 i;
	 for(i=7;i>=0;i--)
	 {
		 SCL=1; 			//slave write
		 if(SDA==1) 		//when SDA line is 1 than only data is present
			 temp|=(1<<i);
		 SCL=0; 			//make zero after reading 1 bit
	 }
	 return temp;
 }
 
 /*--I2C ACKNOWLEDGEMENT--*/
 bit i2c_Ack()
 {
 	SCL=0;			   //8th clk pulse is zero 
	SDA=1;		  //data available in SDA line
	SCL=1;		//9th clock pulse
	_nop_();
	if(SDA==0)
	{
		SCL=0;				//to write next bit make zero
		return 0;
	}
	else
	{
		SCL=0;			   //to write next bit make zero
		return 1;
	}
 }
 /*--I2C NOACK--*/
 void i2c_NoAck()
 {
	 SCL=0;
	 SDA=1;
	 SCL=1;
 }

