#include "tm4c123gh6pm.h"
#define GPIO_SWL 0
#define GPIO_SW2 1
#define GPIO_SW_NOT_PRESSED 1


 
void Init_PortF ();
unsigned char readSwitch(int x);
void setLEDs(unsigned char data);