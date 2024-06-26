#include "../includes/GPS.h"
#include "../includes/UART.h"
#include "../includes/GPIO.h"
#include "tm4c123gh6pm.h"
#include "String.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double take_longitude(char point[]){
	char longitude_str[16] = {0};
	char degrees_str[16] = {0};
	char minutes_str[16] = {0};
	double longitude;
	strncpy(longitude_str  , point  , 8);

    longitude_str[8]='\0';

	strncpy(degrees_str , longitude_str , 2);
	degrees_str[2] = '\0';
	strncpy(minutes_str , longitude_str +2 , 7);
    minutes_str[7] = '\0';

	longitude = strtod(degrees_str,NULL) + strtod(minutes_str , NULL) / 60 ;
	return longitude;

}


double take_latitude(char point[]){
	char latitude_str[16] = "";
	char degrees_str[16] = "";
	char minutes_str[16] = "";
	double latitude ;
	strncpy(latitude_str  , point + 9 , 9);
    latitude_str[9] = '\0';

	strncpy(degrees_str , latitude_str , 3);
	degrees_str[3] = '\0';
	strncpy(minutes_str , latitude_str + 3 , 6);
    minutes_str[6] = '\0';
	latitude = strtod(degrees_str,NULL) + strtod(minutes_str , NULL) / 60 ;
	return latitude;

}

//-------------------------------------//

#define R 6378137 // Radius of the Earth in meters
#define M_PI 3.14159265358979323846
double toRadians(double degree) {
    return degree * M_PI / 180.0;
}

double haversine(double lat1, double lon1, double lat2, double lon2) {
		double dlat;
		double dlon;
		double a;
		double c;
		double distance;
  // Convert degrees to radians

    lat1 = toRadians(lat1);
    lon1 = toRadians(lon1);
    lat2 = toRadians(lat2);
    lon2 = toRadians(lon2);

    // Haversine formula
     dlat = lat2 - lat1;
     dlon = lon2 - lon1;
     a = sin(dlat / 2) * sin(dlat / 2) + cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2);
     c = 2 * atan2(sqrt(a), sqrt(1 - a));
     distance = R * c;

    return distance;
}
void extract_Detailed_Location_info(char Location[] , char detailed_location[]){
		const char delimitar[] = ",";

		const char Point_start_and_end[] = "\n";
		const char seperator[] = ",";

		char *token = strtok(Location,  delimitar);
		int field_index = 0;
		while (token != NULL) {

					if (field_index == 3  ) { //latitude
						strcat(detailed_location, token );
					}

					if (field_index == 5  ) { //longitude
						strcat(detailed_location,seperator );
						strcat(detailed_location, token );
						strcat(detailed_location, Point_start_and_end );
					}

					token = strtok(NULL, delimitar);
					field_index++;
			}

}


//-------------------------------------//

void Take_instant_location(char result_point[]){


	while(1){
        char point[1000];
        int len = 10000;
        char log_command[50];
		Parse_GPS_command(point , len , log_command);

		if( (strcmp(log_command,"$GPRMC") == 0)){
            strcpy(result_point , point);
			break;
		}

	}

}

//-------------------------------------//

void implement_GPS_fix(){
	int len = 10000;

	while(1){
        char point[50] ;
        char log_command[50];
		Parse_GPS_command(point , len , log_command);
		if( (strcmp(log_command,"$GPRMC") == 0) && check_GPS_FIX(point) ){
			break;
		}

	}

}


int check_GPS_FIX(char *chs){
	//$GGGAS , 12, A,123123
	const char delimitar[] = ",";
	char *token = strtok(chs,  delimitar);
	int field_index = 0;
	 while (token != NULL) {
					if (field_index == 2) { // The Fix Quality field is typically the 7th field in a GGA sentence
						if(strcmp(token, "A") == 0){
							return 1; // Convert the token to integer and return as Fix Quality
						}
						break;
					}
					token = strtok(NULL, delimitar);
					field_index++;
			}
	return 0;

}

void Parse_GPS_command(char *chs , int len,char log_Name[]){
		getCommand(chs,len,'$','*');
		strncpy(log_Name , chs , 6);

}



//-------------------------------------//
void getCommand(char *command , int len , char start , char end){
	//
	char character;
	int i;
	//flag to indicate whether to read data or not
	int isParsed = 0;
	for(i =0 ; i<len ; i++){
		character = read_UART1();
		
		if(character == start)
		{
			isParsed = 1;
			i = 0 ;
			continue;
		}
		
		if(isParsed )
			command[i] = character;
		
	  if (character == end)
			break;
	}
}



