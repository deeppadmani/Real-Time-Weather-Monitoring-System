typedef unsigned char u8;
typedef signed   char s8;
typedef unsigned int u16;
typedef signed int s16;
void i2c_start(void);
void i2c_stop(void);
void i2c_write(u8 d);
u8 i2c_read(void);
bit i2c_ack(void);
void i2c_noack(void);
void i2c_byte_write(u8 sa,u8 mr,u8 d);
u8 i2c_byte_read(u8 sa,u8 mr);

void uart_init(u16 baud);
void uart_tx(u8 ch);
void uart_tx_string(s8 *s);

void delay_ms(u16 ms);

u16 read_adc(void);


