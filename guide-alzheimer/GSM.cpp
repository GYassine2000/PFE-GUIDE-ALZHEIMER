#include "HardwareSerial.h"
#include "GSM.h"
#include <RTClib.h>

String phoneNumber = "+33695202814";
float distanceLimit = 5;
float freq = 1; /// frequency in minute
//RTC_PCF8523 rtc1;
bool firstSms = true;
//DateTime now = rtc1.now();

void setupGSM() {
  GSM.begin(9600);
}


void loopGSM(float distance, bool issentSMS) {
  calculateSendingSMS(distance, issentSMS);
}

void sendSMS() {
  setupGSM();
  
  Serial.println(">>>>>>>>>>>>>>>>>>>>>> Envoyer le SMS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"); 
  delay(1000);

  GSM.println("AT");
  updateSerial();

  GSM.println("AT+CMGF=1"); 
  updateSerial();

  GSM.println("AT+CMGS=\""+phoneNumber+"\"");
  updateSerial();

  String message = "Hello Yassine, The person you are taking care of has exceeded the distance limit. You can go pick him/her up at this location : https://www.google.com/maps/place/48%C2%B053'49.2%22N+2%C2%B011'14.4%22E/@48.897,2.1873333,17z/data=!3m1!4b1!4m4!3m3!8m2!3d48.897!4d2.1873333?entry=ttu";

  GSM.print(message);
  updateSerial();

  GSM.write(26);

  delay(2000);

  Serial.println(">>>>>>>>>>>>>>>>>>>>>> Attendre de recevoir le SMS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"); 
  delay(3000);
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
  //if (/*rtc1.now().secondstime() - now.secondstime()*/freq*60 >= freq*60 || firstSms) {
    if (distance > distanceLimit) {
      if (keepSend) {
        //now = rtc1.now();
        //firstSms = false;
        sendSMS();
      }
    }
  //}
}
