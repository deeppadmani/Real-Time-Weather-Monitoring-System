/*header.h*/

#include<reg51.h>

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u16;
typedef signed int s16;
typedef unsigned long int u32;
typedef signed long int s32;
typedef float s32_f;

#define HIGH 1
#define LOW 0
#define PORT0 0
#define PORT1 1
#define PORT2 2
#define PORT3 3

extern void  delay_ms(u16 ms);

extern void i2c_start(void);
extern void i2c_stop(void);
extern void i2c_write(u8 info);
extern u8 i2c_read(void);
extern bit i2c_Ack(void);
extern void i2c_NoAck(void);

extern void i2c_Device_Write(u8 SlaveId,u8 Command,u8 info);
extern u8 i2c_Device_Read(u8 SlaveId,u8 Command);
extern s16 i2c_device_read_temp(void);
extern void i2c_cmd_write(u8 sa,u8 cmd);
//extern void i2c_write_string(u8 sa,u8 mr,const char *s);
extern void i2c_Page_Write(u8 SlaveId,u8 SlaveMemoryId,u8 Count,u8 *info);
//extern void i2c_read_string(u8 sa,u8 mr,u8 *buf);
extern void i2c_Page_Read(u8 SlaveId,u8 SlaveMemoryId,u8 Count,u8 *ubuf);
extern void temp_init(void);

extern void uart_init(u16 baud);
extern void uart_tx(u8 byte);
//extern u8 uart_rx(void);
extern void uart_string(s8 *ptr);
//extern void uart_rx_string(s8 *buf,u8 MaxSize);
extern void uart_int(s16 temp);
extern void uart_float(s32_f n);
//extern void uart_hex(s16 number);

extern u16 Adc_Read(u8 channel);

extern void lcd_cmd(u8 cmd);
extern void lcd_init(void);
extern void lcd_char(u8 ch);
extern void lcd_int(s16 n);
extern void lcd_float(s32_f n);
extern void lcd_string(char *str);

extern void RTC_init(void);
extern void RTC_read(void);

extern void Ext_INT0_Init();