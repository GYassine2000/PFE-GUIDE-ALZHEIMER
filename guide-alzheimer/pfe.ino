#include <SoftwareSerial.h>
#include "GPS.h"
#include "GSM.h"
#include "ALERT.h"

float distance;
bool keepSend = true;

void setup() {
  Serial.begin(9600);
  
  setupGSM();
  setupGPS();
  setupClock();

  delay(1000);
}

void loop() {
  loopAlert();
  distance = loopGPS();
  loopGSM(distance, keepSend);
}

