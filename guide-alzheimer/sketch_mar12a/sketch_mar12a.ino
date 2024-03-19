#include <Adafruit_GPS.h>    //Install the adafruit GPS library
#include <SoftwareSerial.h> //Load the Software Serial library

SoftwareSerial mySerial(0,1); //Initialize the Software Serial port
Adafruit_GPS GPS(&mySerial); //Create the GPS Object

String NMEA1; //Variable pour la premier NMEA 
String NMEA2; //Variable pour la deuxiéme NMEA 
String latitude;
String lat;
String longitude;
String lon;
String altitude;

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
  
}

void readGPS() {
  
  clearGPS();
  while(!GPS.newNMEAreceived()) { //Bouclez jusqu'à ce que vous ayez une nouvelle NMEA
    c=GPS.read();
  }
  GPS.parse(GPS.lastNMEA()); //ecrire la dernière nouvelle NMEA
  NMEA1=GPS.lastNMEA();
  
   while(!GPS.newNMEAreceived()) { //Bouclez jusqu'à ce que vous ayez une nouvelle NMEA
    c=GPS.read();
  }
  GPS.parse(GPS.lastNMEA()); //ecrire la dernière nouvelle NMEA
  NMEA2=GPS.lastNMEA();
  
  Serial.println(NMEA1);
  Serial.println(NMEA2);
  Serial.println("");
  
}

void clearGPS() {  //Supprimer les anciennes donner du MNEA1 et MNEA2
  while(!GPS.newNMEAreceived()) { //Bouclez jusqu'à ce que vous ayez une nouvelle NMEA
    c=GPS.read();
  }
  GPS.parse(GPS.lastNMEA()); //ecrire la dernière nouvelle NMEA
  
  while(!GPS.newNMEAreceived()) { //Bouclez jusqu'à ce que vous ayez une nouvelle NMEA
    c=GPS.read();
  }
  GPS.parse(GPS.lastNMEA()); //ecrire la dernière nouvelle NMEA
  while(!GPS.newNMEAreceived()) { //Bouclez jusqu'à ce que vous ayez une nouvelle NMEA
    c=GPS.read();
  }
  GPS.parse(GPS.lastNMEA()); //ecrire la dernière nouvelle NMEA
}