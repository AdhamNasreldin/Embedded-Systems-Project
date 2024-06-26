
#include <stdint.h>
#include "tm4c123gh6pm.h" // header file of tivaC
#include "io.h"



void RGBLED_Init(void)
{    
    volatile unsigned long delay;
    SYSCTL_RCGCGPIO_R  |= 0x20;            // PortF clock enable
    while ((SYSCTL_PRGPIO_R & 0x20)==0){}; // Delay
    GPIO_PORTF_LOCK_R   = GPIO_LOCK_KEY;   // Unlock PortF Commit register
    GPIO_PORTF_CR_R    |= 0x0E;            // Allow changes to PF321
    GPIO_PORTF_AMSEL_R &= ~0x0E;           // Disable analog function 
    GPIO_PORTF_PCTL_R  &= ~0x0000FFF0;     // GPIO clear bit PCTL 
    GPIO_PORTF_AFSEL_R &= ~0x0E;           // No alternate function 
    GPIO_PORTF_DIR_R   |= 0x0E;            // PF321 output 
    GPIO_PORTF_DEN_R   |= 0XOE;            // Enable digital pins PF4-PFO 
    GPIO_PORTF_DATA_R  &= ~0xOE;           // Initialize LEDs to be off    
}



void init_GPIO(void) 
{
    SYSCTL_RCGCGPIO_R |= 0x20;    // Enable clock for PORTF (bit 5)
    GPIO_PORTF_DIR_R  |= 0x08;     // Set PF3 (green LED) as output (bit 3)
    GPIO_PORTF_DEN_R  |= 0x08;     // Enable digital function for PF3 (bit 3)
    GPIO_PORTF_DIR_R  &= ~0x10;    // Set PF4 (push button) as input (bit 4)
    GPIO_PORTF_DEN_R  |= 0x10;     // Enable digital function for PF4 (bit 4)
}


void toggleGreenLED(void) 
{
    if ((GPIO_PORTF_DATA_R & 0x10) == 0) 
    {
        // Button is pressed (PF4 is low)
        GPIO_PORTF_DATA_R ^= 0x08; // Toggle the green LED (PF3)
    }
}


int main(void) 
{
    init_GPIO();
    while (1) 
    {
        toggleGreenLED();
    }
    return 0;
}
