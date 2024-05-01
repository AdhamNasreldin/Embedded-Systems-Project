#include "tm4c123gh6pm.h"
#define GPIO_SWL 0
#define GPIO_SW2 1
#define GPIO_SW_NOT_PRESSED 1


 /// Port LED color*///
 #define GPIO_RED_LED O

#define GPIO_GREEN LED 1
#define GPIO_BLUE LED 2
/// Port LED state on/off*///

#define GPIO_LED_ON 1

#define GPIO_LED_OFF O
/////////-functions///////
 void GPIO_initPortB();


void GPIO_initPort(void);


unsigned char GPIO_getSwitchesValue (unsigned char sw);


void GPIO_setLedValue (unsigned char ledColor, unsigned char ledState);

 void GPIO_PORTB_setPort (unsigned char sevenSegmentValues);

 void GPIO_setSevenSegment (unsigned char valueOfSevenSegment);