# include"tm4c123gh6pm.h"

void UART0_Int(){
    SYSCTL_RCGCUART_R  |= SYSCTL_RCGCUART_R0 ;  // enable clock of UART
    SYSCTL_RCGCGPIO_R  |= SYSCTL_RCGCUART_R0 ;  // enable clock of GPIO_A
    // no delay required
    UART0_CTL_R &= ~ UART_CTL_UARTEN ; // disable UART
    // set BR = 9600 bits/sec
    UART0_IBRD_R = 104 ;
    UART0_FBRD_R = 11  ;
    UART0_LCRH_R = ( UART_LCRH_WLEN_8 | UART_LCRH_FEN ) ; // enable FIFO (8 bit word)
    UART0_CTL_R  |= (UART_CTL_UARTEN | UART_CTL_RXE | UART_CTL_TXE) ; // enable TX and RX and UART

    // connection with GPIO

    GPIO_PORTA_AFSEL_R |= 0x03 ; // bits 0 , 1 will be enabled in ALT.FN
    GPIO_PORTA_PCTL_R  = (GPIO_PORTA_PCTL_R & ~ 0xff) | ( GPIO_PCTL_PA0_U0RX | GPIO_PCTL_PA1_U0TX ) ; // first clear LS 8 bits then enable ALT.FN in PCTL
    GPIO_PORTA_DEN_R   |= 0x03 ; // enable Digital Function
    GPIO_PORTA_AHB_AMSEL_R &= ~ 0x03 ; // disable Analog Function
}