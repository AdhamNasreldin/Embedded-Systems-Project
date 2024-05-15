
#include "../includes/UART.h"

//-------------------------------------//
void UART2_init(void){
	// here we use UART2 for PORTD
		SYSCTL_RCGCUART_R 	|=0X04;
		SYSCTL_RCGCGPIO_R  	|=0X08;
		while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R3) == 0); // Wait until port D clock is connected	
		 // Enable commiting changes
		GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY; // Unlock port D for changes
		GPIO_PORTD_CR_R = 0xC0; // Allow commiting changes to UART2 Pins of Port D

		// Configure UART2
    UART2_CTL_R &= ~UART_CTL_UARTEN;    // Disable the UART
    UART2_IBRD_R = 104; // Setup the BaudRate to be 9600
    UART2_FBRD_R = 11;  // Setup the BaudRate to be 9600
    UART2_CC_R |= UART_CC_CS_SYSCLK; // Connect system clock to UART2
    UART2_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN); // Word length 8, Enable FIFO, No parity
    UART2_CTL_R = (UART_CTL_UARTEN | UART_CTL_RXE | UART_CTL_TXE);  // Enable UART2, RX, TX

    // Configure GPIO pins of port D (PD7 -> Tx and PD6 -> Rx)
    GPIO_PORTD_DEN_R = 0xC0;    // Digial enable UART2 Pins
    GPIO_PORTD_AMSEL_R = 0; // Disable analog mode
    GPIO_PORTD_AFSEL_R = 0xC0;  // Enable alternative funcion for PD6 and PD7
    GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R & 0x00FFFFFF) | (GPIO_PCTL_PD6_U2RX | GPIO_PCTL_PD7_U2TX); // PD5 and PD6 act as UART pins

}
 void uart2_send(uint8_t character) {
while((UART2_FR_R & UART_FR_TXFF) != 0);    // wait until the transmitter buffer isn't full
 UART2_DR_R = character;
    }
/*
Sends string over UART2.
Takes:
char * string: pointer to string (char array) to send over UART.
*/
void uart2_send_string(char * string) {
    while(*string) {
        uart2_send(*string);
        string++;
    }
}
/*
A function that receives character from UART2
*/
char uart2_receive(void) {
    while ((UART2_FR_R & UART_FR_RXFE) != 0);   // wait till you recieve data
    return (unsigned char)(UART2_DR_R & 0xFF);
}
/*
A function that receives string over UART2.
Takes:
1. char * string: pointer to character array, where to store the received characters
2. uint32_t len: length of array where to store characters
*/
void uart2_receive_string(char * string, uint32_t len) {    // Not complete
    char received;
    int i;
    for(i = 0; i < len; i++) {
        received = uart2_receive();
        string[i] = received;
    }
}
/*
A function that send character through UART5.
*/
void UART1_init(){
	// here we use UART2 for PORTB
	SYSCTL_RCGCUART_R 	|= 0X02;
	SYSCTL_RCGCGPIO_R  	|=  0X02;
	
	while((SYSCTL_PRGPIO_R & 0x02)==0);
	
	UART1_CTL_R &= ~ UART_CTL_UARTEN ;
	UART1_IBRD_R  			=0x68;          
	UART1_FBRD_R 				=0x0B;
	
	// here there is no difference so we use the same masks
	
	UART1_CTL_R 				=0X0301;			
	UART1_LCRH_R 				=0x0070;
	
	// in PORTA UART0 was on pins 0 AND 1 SO WE USED 0X03 AS a mask 
	//but here in PORTD UART1 is on pins 1 and 2 so we use 0x03 as a mask 
	
	GPIO_PORTB_AFSEL_R  |=0x03;
	GPIO_PORTB_PCTL_R		= (GPIO_PORTB_PCTL_R &0XFFFFFF00 )+ 0X00000011;
	GPIO_PORTB_DEN_R |=0X03;
	GPIO_PORTB_AMSEL_R &= ~0X03;
	
}
void write_UART1(unsigned char data){
	while( (UART1_FR_R & 0X0020) != 0);
	UART1_DR_R = data;
}

unsigned char read_UART1(){
	while((UART1_FR_R & 0x0010) != 0);
	return (unsigned char) (UART1_DR_R & 0xFF );
}

