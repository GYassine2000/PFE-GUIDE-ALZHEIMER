#ifndef GPS_H
#define GPS_H
#include<Arduino.h>

void setupGPS();

float loopGPS();

void readGPS();

void clearGPS();

float calculateDistance(float latitude, float longitude, float latitudeReference, float longitudeReference);

void convertCoordinatesGPS(float coordinate, char direction, float &degrees, float &minutes, float &seconds);

#endif
