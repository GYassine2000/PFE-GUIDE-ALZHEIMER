#include <SoftwareSerial.h>
#include "GPS.h"
#include "GSM.h"
#include "ALERT.h"
#include "httprequests.h"

float distance;
bool keepSend = true;
String apnLycamobile = "data.lycamobile.de";
String urlGps = "https://findgrandma-ee022-default-rtdb.europe-west1.firebasedatabase.app/gps.json";
String urlSim = "https://findgrandma-ee022-default-rtdb.europe-west1.firebasedatabase.app/sim.json";
String urlAlerts = "https://findgrandma-ee022-default-rtdb.europe-west1.firebasedatabase.app/alerts.json";

void setup() {
  Serial.begin(9600);

  setupGPS();

  setupGSM();

  setupClock();

  setupHTTP(urlGps, apn);
  setupHTTP(urlSim, apn);
  setupHTTP(urlAlerts, apn);

  delay(1000);
}

void loop() {

  distance = loopGPS();

  loopHorloge();
  
  loopGSM(distance, keepSend);
  keepSend = false;

  loopHTTP();
}

