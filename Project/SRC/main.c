
#include "../includes/GPIO.h"
#include "../includes/UART.h"
#include "tm4c123gh6pm.h"
#include "../includes/Delay.h"
#include "../includes/GPS.h"
# define Red_Led 0X02
# define Blue_Led 0x04
# define  Green_Led 0x08


// int IsButtonPressed() ;





int main ()
{char *point_command = "";
	char *point = "";
	char *trajectory = "";
	char *previous_point = "";
	double total_distance;
	const int len = 10000;
	char start_point_command[50] = "";
	char start_point[30] = "";
	char command[len] = {0};
	UART1_init();
	implement_GPS_fix();
	systick_init();
	UART2_init();

	//
	Take_instant_location(start_point_command );
	extract_Detailed_Location_info(start_point_command  , start_point );
	

	strcpy(previous_point , start_point);
	total_distance = 0;
	
	while(1){
		double distance;
		double point1_lat;
		double point1_lon;
		double point2_lat ;
		double point2_lon;
		Take_instant_location(point_command );
		extract_Detailed_Location_info(point_command  , point );
		strcat(trajectory , point);
		
	
		point1_lat = take_latitude(previous_point); 
    point1_lon = take_longitude(previous_point);
		
		
    point2_lat = take_latitude(point); 
    point2_lon = take_longitude(point);
		
    // Calculate distance
		
    distance = haversine(point1_lat, point1_lon, point2_lat, point2_lon);
		total_distance += distance;
		if(total_distance >= 100) break;
    //printf("Distance between the two points: %.2f meters\n", distance);
		
    strcpy(previous_point,point);
		point_command = "";
		point = "";
		
	}
	while(1){
	char rec=uart2_receive();
		if(rec=='U'){
			uart2_send_string(trajectory);
		break;}
	
	}
	
	
	 // Example coordinates in degrees and minutes
  
	
}
