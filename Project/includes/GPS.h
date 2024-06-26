
#include "stdint.h"
#include "tm4c123gh6pm.h"
#include "String.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define R 6371000 // Radius of the Earth in meters
#define M_PI 22/7
void implement_GPS_fix(void);
int check_GPS_FIX(char *chs);
void Parse_GPS_command(char *chs , int len,char *log_Name);
void extract_Detailed_Location_info(char *Location , char *detailed_location);
void Take_instant_location(char *point);
void getCommand(char *command , int len , char start , char end);
double take_longitude(char *point);
double take_latitude(char *point);

double haversine(double lat1, double lon1, double lat2, double lon2);
void extract_Detailed_Location_info(char *Location , char *detailed_location);
void Take_instant_location(char *point);

