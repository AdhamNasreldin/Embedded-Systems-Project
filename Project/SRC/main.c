# include "tm4c123gh6pm.h"
#include "../includes/GPIO.h"


int IsButtonPressed() ; 
void Init_UART() ; 
void Init_PortF() ; 


 
 
int main () 
{
  Init_UART () ;
	Init_PortF () ; 
	int distance =0 ; 
	
	// some code 
	
	while(1) 
	{
		// some code
		if( IsButtonPressed() ) 
			break ; 
	
	}

return 0 ; 
}