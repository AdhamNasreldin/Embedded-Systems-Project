#include "tm4c123gh6pm.h"
#include "stdint.h"
void UART2_init(void);
void uart2_send(uint8_t character);
void uart2_send_string(char * string);
char uart2_receive(void);
void uart2_receive_string(char * string, uint32_t len);
unsigned char read_UART1(void);
void UART1_init(void);
void write_UART1(unsigned char data);
void UART_OutString(char *chs);void getCommand(char *command , int len , char start , char end);void write_UART2(char data);char read_UART2();void uart2_init();

