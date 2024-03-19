#include <Adafruit_GPS.h>
#include <SoftwareSerial.h> //Load the Software Serial library
#include <Math.h>
SoftwareSerial mySerial(0,1); //Initialize the Software Serial port
Adafruit_GPS GPS(&mySerial); //Create the GPS Object

String NMEA1; //Variable pour la premier NMEA 
String NMEA2; //Variable pour la deuxiéme NMEA 
String latitude;
String lat;
String longitude;
String lon;
String altitude;
float distance;
char c; //permet de lire les caractères provient de la GPS

void setup() {
  
  Serial.begin(115200); //Permet d'initialiser le moniteur série à 115200 bauds
  GPS.begin(9600); //Permet d'initialiser GPS à 9600 bauds
  GPS.sendCommand("$PGCMD,33,0*6D");  //Turn off antenna update nuisance data
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); //récepter les informations liées à les RMC et GGA 
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); //Set update rate to 1 hz
  delay(1000); 

}

void loop() {
  
  readGPS();

  if(GPS.fix==1) { 

   latitude=GPS.latitude;
   lat=GPS.lat;
   longitude=GPS.longitude;
   lon=GPS.lon;
   altitude=GPS.altitude;

  }
   calculerDistance(float latitude, float longitude, float latitudeReference, float longitudeReference)
}

void readGPS() {
  
  clearGPS();
  while(!GPS.newNMEAreceived()) { //Loop until you have a good NMEA sentence
    c=GPS.read();
  }
  GPS.parse(GPS.lastNMEA()); //Parse that last good NMEA sentence
  NMEA1=GPS.lastNMEA();
  
   while(!GPS.newNMEAreceived()) { //Loop until you have a good NMEA sentence
    c=GPS.read();
  }
  GPS.parse(GPS.lastNMEA()); //Parse that last good NMEA sentence
  NMEA2=GPS.lastNMEA();
  
  Serial.println(NMEA1);
  Serial.println(NMEA2);
  Serial.println("");
  
}

void clearGPS() {  //Clear old and corrupt data from serial port 
  while(!GPS.newNMEAreceived()) { //Loop until you have a good NMEA sentence
    c=GPS.read();
  }
  GPS.parse(GPS.lastNMEA()); //Parse that last good NMEA sentence
  
  while(!GPS.newNMEAreceived()) { //Loop until you have a good NMEA sentence
    c=GPS.read();
  }
  GPS.parse(GPS.lastNMEA()); //Parse that last good NMEA sentence
  while(!GPS.newNMEAreceived()) { //Loop until you have a good NMEA sentence
    c=GPS.read();
  }
  GPS.parse(GPS.lastNMEA()); //Parse that last good NMEA sentence
}
void calculerDistance(float latitude, float longitude, float latitudeReference, float longitudeReference) {
  //Convert latitude and longitude from degrees to radians
    latitude = radians(latitude);
    longitude = radians(longitude);
    latitudeReference = radians(latitudeReference);
    longitudeReference = radians(longitudeReference);

    //Haversine formula
    float dlon = longitudeReference - longitude;

    float dlat = latitudeReference - latitude
    float a = pow(sin(dlat / 2), 2) + cos(latitude) * cos(latitudeReference) * pow(sin(dlon / 2), 2);
    float c = 2 * atan2(sqrt(a), sqrt(1 - a));
    float r = 6371;  // Radius of Earth in kilometers
    distance = r * c;

    Serial.print("distance: ");
    Serial.println(distance);
