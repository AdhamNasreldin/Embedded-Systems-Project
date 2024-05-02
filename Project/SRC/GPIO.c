#include "../includes/GPIO.h"
void Init_PortF (void) {
SYSCTL_RCGCGPIO_R |= 0x20;
while( (SYSCTL_PRGPIO_R & 0x20)==0);
GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
GPIO_PORTF_CR_R |= 0x1F;
GPIO_PORTF_AFSEL_R &= 0x00;
GPIO_PORTF_AMSEL_R &=0x00;
GPIO_PORTF_DEN_R |= 0x1F;
GPIO_PORTF_PCTL_R &= 0x00000000 ;
GPIO_PORTF_PUR_R = 0x11;
GPIO_PORTF_DIR_R |= 0x0E;
GPIO_PORTF_DATA_R &=~ 0x0E;
}
unsigned char readSwitch(int x) {
if(x==0)
return GPIO_PORTF_DATA_R & 0x01;                                                     
 else // if (x==1)
 return GPIO_PORTF_DATA_R & 0x10; 
}  

void setLEDs(unsigned char data) {
 GPIO_PORTF_DATA_R &= ~0x0E;
 GPIO_PORTF_DATA_R |= data;
 }
