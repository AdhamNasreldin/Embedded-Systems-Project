#include "tm4c123gh6pm.h"


/*  
		 PA7 --> D0
		 PA6 --> D1 
    	 PA5 --> D2 
		 PA4 --> D3
		 PA3 --> D4 
		 PA2 --> D5 
		 PB7 --> D6
		 PB6 --> D7
		 PB5 --> RS
		 PB4 --> RW
		 PB2 --> EN
		
*/

void Printdata(unsigned char data){ // data = 8 bit hexadecimal data

		if ((data&0x01) ==0x01) {GPIO_PORTA_DATA_R |= 0x80;}
		else                   {GPIO_PORTA_DATA_R &= ~0x80;}
		if ((data &0x02) ==0x02) {GPIO_PORTA_DATA_R |= 0x40;}
		else                   {GPIO_PORTA_DATA_R &= ~0x40;}
		if ((data &0x04)==0x04) {GPIO_PORTA_DATA_R |= 0x20;}
		else                   {GPIO_PORTA_DATA_R &= ~0x20;}
		if ((data &0x08) ==0x08) {GPIO_PORTA_DATA_R |= 0x10;}
		else                   {GPIO_PORTA_DATA_R &= ~0x10;}
		if ((data &0x10) ==0x10) {GPIO_PORTA_DATA_R |= 0x08;}
		else                   {GPIO_PORTA_DATA_R &= ~0x08;}
		if ((data &0x20) ==0x20) {GPIO_PORTA_DATA_R |= 0x04;}
		else                   {GPIO_PORTA_DATA_R &= ~0x04;}
		if ((data &0x40) ==0x40) {GPIO_PORTB_DATA_R |= 0x80;}
		else                   {GPIO_PORTB_DATA_R &= ~0x80;}		
		if ((data &0x80) ==0x80) {GPIO_PORTB_DATA_R |= 0x40;}
		else                   {GPIO_PORTB_DATA_R &= ~0x40;}

}

	
void lcd_init(void) {

        SYSCTL_RCGCGPIO_R |= 0x03;    //enable the clock of GPIO A,B
        GPIO_PORTA_DEN_R  |= 0xFC;   //Digitalize these 8 pins
        GPIO_PORTB_DEN_R  |= 0xF4;
        GPIO_PORTA_DIR_R  |= 0xFC;    	//config these 8 pins as output pins
        GPIO_PORTB_DIR_R  |= 0xF4;
	
	  
		lcd_cmd(0x38); //8bit mode utilising 16 columns and 2 rows
		lcd_cmd(0x06); // autoincrementing the cursor when prints the data in current		
		lcd_cmd(0x0C); //cursor off and display on
		lcd_cmd(0x01); //clearscreen		
}




	void load_Time(long d)
{
   while(d--);
}
		
	void lcd_data(unsigned char data)
	{
     Printdata(data);                  //pass the data in the datalines of lcd
     GPIO_PORTB_DATA_R &= ~ 0x10 ;    //turn of the R/W pin for write operation in lcd
     GPIO_PORTB_DATA_R |= 0x20;      //turn on the RS for writing to the data register of lcd
     GPIO_PORTB_DATA_R |= 0x04;     //turn on the En of lcd for enabling the clock of lcd
     load_Time(10000);                            //wait for sometime
     GPIO_PORTB_DATA_R &=~ 0x04;             //Turn off the En of lcd		
	
	}
	
	
	
  void lcd_command(unsigned char cmd){
	   
		 Printdata(cmd);                  //pass the 8bit data in the datalines of lcd
     GPIO_PORTB_DATA_R &= ~ 0x10 ;    //turn off the R/W pin for write operation in lcd
     GPIO_PORTB_DATA_R &= ~ 0x20;     //turn off the RS for writing to the instruction register of lcd
     GPIO_PORTB_DATA_R |= 0x04;       //turn on the En of lcd for enabling the clock of lcd
     load_Time(10000);                    //wait for sometime
     GPIO_PORTB_DATA_R &=~ 0x04;      //Turn off the En of lcd		
		
  }
	
	
	void lcd_string_Input(unsigned char *str ,unsigned char len){
	
unsigned char i;
	  for (i=0;i<len;i++){
		lcd_data(str[i]);
		}
	}
	
	
