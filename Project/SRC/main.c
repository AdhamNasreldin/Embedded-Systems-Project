
#include "../includes/GPIO.h"
#include "../includes/UART.h"
#include "tm4c123gh6pm.h"
#include "../includes/Delay.h"
#include "../includes/GPS.h"
# define Red_Led 0X02
# define Blue_Led 0x04
# define  Green_Led 0x08


// int IsButtonPressed() ;



int main() {
    char first_point_command[100] = {0};
    char previous_point[100] = {0};
    char first_point[100] = {0};

    //get_NMEAdata();
    implement_GPS_fix();

    double total_distance = 0;

    Take_instant_location(first_point_command);
    extract_Detailed_Location_info(first_point_command, first_point);
    //char command3[1000] = {0};
    strcpy(previous_point ,first_point);



   // Take_instant_location(command3);
    //extract_Detailed_Location_info(command3, command4);

    while(1){

    char current_point_command[100] = {0};
    char current_point[100] = {0};

    double long1, lat1, long2, lat2, distance;

    // Get the first location
    Take_instant_location(current_point_command);
    extract_Detailed_Location_info(current_point_command, current_point);
    //filter_point(command2);
    printf("Current Point: %s", current_point);
   // printf(command2);
    long1 = take_longitude(previous_point);
    lat1 = take_latitude(previous_point);

    // Get the second location

    //filter_point(command4);
   // printf("Second Point: %s\n", command4);
    long2 = take_longitude(current_point);
    lat2 = take_latitude(current_point);
    strcpy(previous_point , current_point);
    // Calculate the distance between the two points
    distance = haversine(lat1, long1, lat2, long2);
    total_distance+=distance;


    //if(total_distance > 100) break;
    printf("\n");
    printf("Distance moved: %f", total_distance);
    printf("\n");

    }



}