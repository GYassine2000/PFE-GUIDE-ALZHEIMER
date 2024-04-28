

Aller au contenu
Utiliser Gmail avec un lecteur d'écran

Se désabonner de Start Daily ?
Vous n'avez ouvert aucun e-mail de cet expéditeur le mois dernier
Se désabonnerNon, merci
Conversations
0,13 Go utilisés sur 15 Go
Conditions d'utilisation · Confidentialité · Règlement du programme
Dernière activité sur le compte : il y a 2 jours
Détails
#include <math.h>
#include <Adafruit_GPS.h> //Load the GPS Library. Make sure you have installed the library form the adafruit site above
#include <SoftwareSerial.h> //Load the Software Serial Library. This library in effect gives the arduino additional serial ports
SoftwareSerial mySerial(3, 2); //Initialize SoftwareSerial, and tell it you will be connecting through pins 2 and 3
Adafruit_GPS GPS(&mySerial); //Create GPS object

String NMEA1;  //utiliser pour le première NMEA
String NMEA2;  //utiliser pour le deuxiéme NMEA
char c;       //utiliser pour lire les caractères renvoyés par le module GPS
float latitude;
float longitude;
float latitudeReference = 51.507;
float longitudeReference = -0.1278;
float lat_degrees, lat_minutes;
float lat_seconds;
float lon_degrees, lon_minutes;
float lon_seconds;
float distance;

void setup()  {
  Serial.begin(9600);  //activer le Serial Monitor
  GPS.begin(9600);       //actier GPS 
  GPS.sendCommand("$PGCMD,33,0*6D"); // Turn Off GPS Antenna Update
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); // prend seulement les informations RMC et GGA NMEA
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  delay(1000);  //Pause
}

void loop() {
  Serial.println("DEMARRAGE................");
  readGPS(); // APPELER LA FONCTION readGPS()
  Serial.println(NMEA1);
  Serial.println(NMEA2);

  if(GPS.fix == 1) { // fix == 1 => signifie que le GPS est en train d'envoyer à la carte Arduino les bonnes informations
    Serial.println("GPS FIXED..................................");
    latitude = GPS.latitude; 
    char lat = GPS.lat;

    Serial.print("latitude before change = ");
    Serial.println(latitude);
    Serial.print("lat before change = ");
    Serial.println(lat);

    longitude = GPS.longitude;
    char lon = GPS.lon;
    Serial.print("longitude before convertion to degree = ");
    Serial.println(longitude);
    Serial.print("lon before convertion to degree = ");
    Serial.println(lon);

    GPS.altitude;

    convertirCoordonnesGPS(latitude, lat, lat_degrees, lat_minutes, lat_seconds); // convertir le latitude reçu depuis le GPS à l'unité (degré) utilisable pour calculer la distance
    latitude = lat_degrees + lat_minutes + lat_seconds; // latitude en degrés
    Serial.print("lat_degrees = ");
    Serial.print(lat_degrees);
    Serial.print(",lat_minutes = ");
    Serial.print(lat_minutes);
    Serial.print(",lat_seconds = ");
    Serial.print(lat_seconds);
    Serial.println();
    Serial.print("latitude = ");
    Serial.println(latitude); // latitude en degrée

    convertirCoordonnesGPS(longitude, lon, lon_degrees, lon_minutes, lon_seconds);// convertir la longitude reçue depuis le GPS à l'unité (degré) utilisable pour calculer la distance
    longitude = lon_degrees + lon_minutes + lon_seconds;// longitude en degrée
     Serial.print("lon_degrees = ");
    Serial.print(lon_degrees);
    Serial.print(",lon_minutes = ");
    Serial.print(lon_minutes);
    Serial.print(",lon_seconds = ");
    Serial.print(lon_seconds);
    Serial.println();
    Serial.print("longitude = "); 
    Serial.println(longitude); // longitude en degrée
  }

  delay(1000);  //Pauser le programme pour donner le temps suffisant au GPS pour envoyer les bonnes informations

  distance = calculerDistance(latitude, longitude, latitudeReference, longitudeReference);

  Serial.print("Distance = ");
  Serial.println(distance);
}

void readGPS() {
  clearGPS();    //supprimer les nouveaux dernières informations du GPS pour libérer son l'espace memoire
  while(!GPS.newNMEAreceived()) { //lire jusqu'à recevoir une nouveau et bonne NMEA 
  c=GPS.read(); //Lire les carractéres recevoir de le GPS
  }
  GPS.parse(GPS.lastNMEA());  //oublier????
  NMEA1=GPS.lastNMEA();      //Once parsed, save NMEA sentence into NMEA1
  while(!GPS.newNMEAreceived()) {  //Go out and get the second NMEA sentence, should be different type than the first one read above.
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

float calculerDistance(float latitude, float longitude, float latitudeReference, float longitudeReference) {
  // Convertir latitude et longitude de degrees à radians
    float mesuredLatitude = radians(latitude);
    float mesuredLongitude = radians(longitude);
    float latitudeReferenceRad = radians(latitudeReference);
    float longitudeReferenceRad = radians(longitudeReference);

    // Haversine formula
    float dlon = longitudeReferenceRad - mesuredLongitude;

    float dlat = latitudeReferenceRad - mesuredLatitude;

    float a = pow(sin(dlat / 2),2) + cos(mesuredLatitude) * cos(latitudeReferenceRad) * pow(sin(dlon / 2),2);
    float b = 2 * atan2(sqrt(a), sqrt(1 - a));
    float r = 6371;  // Rayon de la Terre en kilomètres
    return r * b;
}

void convertirCoordonnesGPS(float coordinate, char direction, float &degrees, float &minutes, float &seconds) {
  // permet de convertir les coordonnées qui envoiyées par le GPS 
  degrees = int(coordinate) / 100; 
  //en minutes
  minutes = (float(int(coordinate) % 100))/60.0; 
  // en secondes
  seconds = 0;  

  // utiliser pour donner les signe de la degré à partir de la direction
  if (direction == 'S' || direction == 'W') {
    degrees = -degrees; // For Southern and Western hemispheres, negate the value ????
  }
}
code_gps_final.txt
Affichage de code_gps_final.txt en cours..