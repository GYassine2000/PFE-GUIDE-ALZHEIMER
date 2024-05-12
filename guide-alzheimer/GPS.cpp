#include "GPS.h"
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(3,2);
Adafruit_GPS GPS(&mySerial);


String NMEA1;  
String NMEA2;
char c; 
float latitude;
float longitude;
float latitudeReference = 51.507;
float longitudeReference = -0.1278;
float lat_degrees, lat_minutes;
float lat_seconds;
float lon_degrees, lon_minutes;
float lon_seconds;

void setupGPS() {
  GPS.begin(9600);
  GPS.sendCommand("$PGCMD,33,0*6D");
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);

  delay(1000);
}


float loopGPS() {

  readGPS();

  float distance;
  if(GPS.fix == 1) {
    latitude = GPS.latitude; 
    char lat = GPS.lat;

    longitude = GPS.longitude;
    char lon = GPS.lon;

    convertCoordinatesGPS(latitude, lat, lat_degrees, lat_minutes, lat_seconds); 
    latitude = lat_degrees + lat_minutes + lat_seconds;
    Serial.print("latitude = ");
    Serial.println(latitude);

    convertCoordinatesGPS(longitude, lon, lon_degrees, lon_minutes, lon_seconds);
    longitude = lon_degrees + lon_minutes + lon_seconds;
    Serial.print("longitude = "); 
    Serial.println(longitude); 

    delay(1000);

    distance = calculateDistance(latitude, longitude, latitudeReference, longitudeReference);
    Serial.print("Distance = ");
    Serial.println(distance);
  }
  return distance;
}


void readGPS(){ 
  clearGPS();   
  while(!GPS.newNMEAreceived()) {
  c=GPS.read();
  }
  GPS.parse(GPS.lastNMEA());  
  NMEA1=GPS.lastNMEA();      
  while(!GPS.newNMEAreceived()) {
    c=GPS.read();
  }
  GPS.parse(GPS.lastNMEA());
  NMEA2=GPS.lastNMEA();
}

void clearGPS() { 
  while(!GPS.newNMEAreceived()) {
    c=GPS.read();
  }
  GPS.parse(GPS.lastNMEA());
  while(!GPS.newNMEAreceived()) {
    c=GPS.read();
  }
  GPS.parse(GPS.lastNMEA());
}

float calculateDistance(float latitude, float longitude, float latitudeReference, float longitudeReference) {
    float mesuredLatitude = radians(latitude);
    float mesuredLongitude = radians(longitude);
    float latitudeReferenceRad = radians(latitudeReference);
    float longitudeReferenceRad = radians(longitudeReference);

    float dlon = longitudeReferenceRad - mesuredLongitude;

    float dlat = latitudeReferenceRad - mesuredLatitude;

    float a = pow(sin(dlat / 2),2) + cos(mesuredLatitude) * cos(latitudeReferenceRad) * pow(sin(dlon / 2),2);
    float b = 2 * atan2(sqrt(a), sqrt(1 - a));
    float r = 6371;  // Radius of Earth in kilometers
    return r * b;
}

void convertCoordinatesGPS(float coordinate, char direction, float &degrees, float &minutes, float &seconds) {
  degrees = int(coordinate) / 100;
  minutes = (float(int(coordinate) % 100))/60.0;
  seconds = 0;

  if (direction == 'S' || direction == 'W') {
    degrees = -degrees;
  }
}

