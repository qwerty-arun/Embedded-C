// Parse GPS String for Time and Coordinates

/*
You are given a $GPRMC NMEA string from a GPS module in the following simplified format:
    $GPRMC,<time>,<status>,<lat>,<NS>,<long>,<EW>,...

Your task is to:
    - Extract and print:
        - UTC time in HH:MM:SS format (first field after $GPRMC)
        - Latitude with direction (lat NS) : NS- North South
        - Longitude with direction (long EW) : EW- East West

Assume:
- Input will always follow this format
- You only need to extract and print the first 7 fields
- Do not validate checksum or GPS fix status

Example-1
Input:
$GPRMC,123519,A,4807.038,N,01131.000,E
Output:
Time: 12:35:19  
Latitude: 4807.038 N  
Longitude: 01131.000 E

Example-2
Input:
$GPRMC,083559,A,3745.678,N,12227.890,W
Output:
Time: 08:35:59  
Latitude: 3745.678 N  
Longitude: 12227.890 W
*/

#include <stdio.h>
#include <string.h>

void parse_gprmc(char *nmea) {
    // Your logic here
    char time[9] = {nmea[7],  nmea[8] , ':' , nmea[9] , nmea[10] , ':' , nmea[11] , nmea[12], '\0'};
    char latitude[11] = {nmea[16],  nmea[17] ,  nmea[18] , nmea[19] , nmea[20] , nmea[21], nmea[22], nmea[23], ' ', nmea[25]};
    char longitude[11] = {nmea[27],  nmea[28] ,  nmea[29] , nmea[30] , nmea[31] , nmea[32], nmea[33], nmea[34], nmea[35], ' ', nmea[37]};
    printf("Time: %s\n", time);
    printf("Latitude: %s\n", latitude);
    printf("Longitude: %s", longitude);
}

int main() {
    char nmea[100];
    fgets(nmea, sizeof(nmea), stdin);
    parse_gprmc(nmea);
    return 0;
}

/*
NMEA defines how GPS data is transmitted over serial/UART as plain ASCII strings, where each line is called a sentence.

Each sentence starts with $, followed by a 5-character identifier (e.g., GPGGA, GPRMC) and a comma-separated list of data fields.

Example: $GPRMC
$GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*6A

This sentence means:

    Field	        Meaning

    $GPRMC	        Sentence type: Recommended minimum GPS data
    123519	        Time: 12:35:19 UTC
    A	            Status: A = Active, V = Void
    4807.038,N	    Latitude: 48°07.038’ N
    01131.000,E	    Longitude: 11°31.000’ E
    022.4	        Speed over ground (knots)
    084.4	        Track angle in degrees
    230394	        Date: 23rd March 1994
    003.1,W	        Magnetic variation
    *6A	            Checksum (XOR of characters after $ and before *)

Why it matters in firmware?
- Real GPS modules output NMEA strings continuously
- You often need to extract location/time info via UART
- Efficient parsing is needed in low-resource environments
*/