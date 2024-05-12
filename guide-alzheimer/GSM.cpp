
#include "GSM.h"
#include <SoftwareSerial.h>

SoftwareSerial GSM(10,11);
String phoneNumber = "+33695202814";
float distanceLimit = 3;

void setupGSM() {
  GSM.begin(9600);
}


void loopGSM(float distance, bool issentSMS) {
  calculateSendingSMS(distance, issentSMS);
}

void sendSMS() {
  setupGSM();
  
  Serial.println("Envoi SMS..."); 
  delay(1000);

  GSM.println("AT");
  updateSerial();

  GSM.println("AT+CMGF=1"); 
  updateSerial();

  GSM.println("AT+CMGS=\""+phoneNumber +"\"");
  updateSerial();

  GSM.print("Bonjour, viens me chercher cher Yassine");
  updateSerial();

  GSM.write(26);

  delay(1000);
}

void updateSerial() {
  delay(500);

  while (Serial.available()) {
    GSM.write(Serial.read());
  }
  while(GSM.available()) {
    Serial.write(GSM.read());
  }
}

void calculateSendingSMS(float distance, bool keepSend) {
  if (distance > distanceLimit) {
    if (keepSend) {
      sendSMS();
    }
  }
}
