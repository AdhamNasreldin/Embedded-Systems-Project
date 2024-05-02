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
