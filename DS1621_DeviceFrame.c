#include"header.h"

/*--I2C BYTE WRITE FRAME--*/
void i2c_Device_Write(u8 SlaveId,u8 Commands,u8 info) //argument slave addr/ memory addr/ data
{ 
	i2c_start();
	i2c_write(SlaveId); 					//write slave addr with write option
	i2c_Ack();
	i2c_write(Commands); 				//write memory aadr
	i2c_Ack();
	i2c_write(info); 						//write data
	i2c_Ack();
	i2c_stop();
}

/*--I2C BYTE READ FRAME--*/
u8 i2c_Device_Read(u8 SlaveId,u8 Commands) 	//argument slave addr/memory addr
{
	u8 temp=0;
	i2c_start();
	i2c_write(SlaveId); 		//dummy  write slave aadr +write option
	i2c_Ack();
	i2c_write(Commands); 	//dummy write memory addr
	i2c_Ack();
	
	i2c_start(); 				//restart condition
	i2c_write(SlaveId|1); 		//read slave addr with read option 
	i2c_Ack();
	temp=i2c_read();
	i2c_NoAck(); 				//optional
	i2c_stop();
	return temp;
}

s16 i2c_device_read_temp(void)
{
	s16 th;
	u8 temp[2],slop,count;
	u16 tempr;
	i2c_cmd_write(0x90,0xEE);
	delay_ms(100);
	i2c_cmd_write(0x90,0x22);
	delay_ms(10);
	//i2c_read_string(0x90,0xAA,temp);
	i2c_Page_Read(0x90,0xAA,2,temp);
	delay_ms(10);
	slop=i2c_Device_Read(0x90,0xA9);
	delay_ms(10);
	count=i2c_Device_Read(0x90,0xA8);
	delay_ms(10);
	tempr=temp[0];
	tempr=(tempr<<8)|temp[1];
	th=(tempr-0.25)+((slop-count)/slop);

	return th;
}

void i2c_cmd_write(u8 sa,u8 cmd)
{
	i2c_start();
	i2c_write(sa);
	i2c_Ack();
	i2c_write(cmd);
	i2c_Ack();
	i2c_stop();
}

/*void i2c_write_string(u8 sa,u8 mr,const char *s)
{
	u8 j=0;
	i2c_start();
	i2c_write(sa);
	i2c_Ack();
	i2c_write(mr);
	i2c_Ack();
	
	while(s[j])
	{
		i2c_write(s[j]);	
		i2c_Ack();
		j++;
	}
	i2c_write(s[j]);	
	i2c_Ack();
	i2c_stop();
//	delay_ms(10);
}

void i2c_read_string(u8 sa,u8 mr,u8 *buf)
{
	u8 i=0;
	i2c_start();
	i2c_write(sa);
	i2c_Ack();
	i2c_write(mr);
	i2c_Ack();

	for(i=0;i<10;i++)//Generic
//	for(i=0;i<2;i++)
	{
		i2c_start();
		i2c_write(sa|1);
		i2c_Ack();		
		buf[i]=i2c_read();
		i2c_NoAck();
		i2c_stop(); 

	}
}		 */

void i2c_Page_Write(u8 SlaveId,u8 SlaveMemoryId,u8 Count,u8 *info)
{
	 u8 i;
	 i2c_start();
	 i2c_write(SlaveId);
	 i2c_Ack();
	 i2c_write(SlaveMemoryId);
	 i2c_Ack();
	 for(i=0;i<Count;i++)
	 {
	 	i2c_write(info[i]);
		delay_ms(10);
		i2c_Ack();
	 }
	 i2c_stop();
}
 /*--I2C PAGE READ FRAME--*/
void i2c_Page_Read(u8 SlaveId,u8 SlaveMemoryId,u8 Count,u8 *ubuf) 	//argument slave addr/memory addr
{
	u8 i;
	i2c_start();
	i2c_write(SlaveId); 		//dummy  write slave aadr +write option
	i2c_Ack();
	i2c_write(SlaveMemoryId); 	//dummy write memory addr
	i2c_Ack();
	i2c_stop();
	
	for(i=0;i<Count;i++)
	{
		i2c_start(); 				//restart condition
 		i2c_write(SlaveId|1); 		//read slave addr with read option
		i2c_Ack();
	 	ubuf[i]=i2c_read();
		i2c_NoAck();
		i2c_stop();		
	} 			
}
 
void temp_init()
{
	u8 te[3];
	i2c_Device_Write(0x90,0xAC,0x02);
	delay_ms(10);
	te[0]=0x28;te[1]=0x0;
	//i2c_write_string(0x90,0xA1,te);
	i2c_Page_Write(0x90,0xA1,2,te);
	delay_ms(10);
	te[0]=0x0A;te[1]=0x0;
//	i2c_write_string(0x90,0xA2,te);
	i2c_Page_Write(0x90,0xA2,2,te);
	delay_ms(10);
}

