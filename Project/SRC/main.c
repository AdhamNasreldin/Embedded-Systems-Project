# include "tm4c123gh6pm.h"
#include "../includes/GPIO.h"

# define Red_Led 0X02
# define Blue_Led 0x04
# define  Green_Led 0x08


// int IsButtonPressed() ;
void Init_UART(void) ;




int main ()
{
  // Init_UART () ;
	Init_PortF () ;
	setLEDs (Red_Led);
	setLEDs (Green_Led) ;
	setLEDs (Blue_Led) ; 
	
return 0 ;
	
}
void PC_UAR2_init(){
	// here we use UART2 for PORTD
	SYSCTL_RCGCUART_R 	|=0X04;
	SYSCTL_RCGCGPIO_R  	|=0X08;
		
	// here there is no difference so we use the same masks
	
	UART2_CTL_R 				=0X0070;			
	UART2_LCRH_R 				=0x0301;
	
}