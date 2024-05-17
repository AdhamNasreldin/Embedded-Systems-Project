void UART_OutString(char *chs){
	while(*chs){
	write_UART0(*chs);
	chs++;
	}
}

void getCommand(char *command , int len , char start , char end){
	//
	char character;
	int i;
	//flag to indicate whether to read data or not
	int isParsed = 0;

	for(i =0 ; i<len ; i++){
		character = read_UART2();
        j++;

		if(character == start)
		{
			isParsed = 1;
			i = 0 ;
			//continue;
		}

		if(isParsed ){
			command[i] = character;

		}
	  if (character == end)
			break;


	}
}
void write_UART2(char data){
	while( (UART2_FR_R & 0X20) != 0);
	UART2_DR_R = data;
}

char read_UART2(){
	while((UART2_FR_R & 0x10) != 0);
	return (unsigned char) UART2_DR_R;
}


void uart2_init() {
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R2; // Enable clock for UART2
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3; // Enable clock for port D GPIO pins
    while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R3) == 0); // Wait until port D clock is connected

    // Enable commiting changes
    GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY; // Unlock port E for changes
    GPIO_PORTD_CR_R = 0xC0; // Allow commiting changes to UART2 Pins of Port D

    // Configure UART5
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

