#include "ALERT.h"
#include <RTClib.h>

RTC_PCF8523 rtc;

int pinAudio = 12;
MedTime drugAppointments[20];

void setupClock () {
  pinMode(ledPin, OUTPUT);
  #ifndef ESP8266
    while (!Serial); // wait for serial port to connect. Needed for native USB
  #endif

    if (! rtc.begin()) {
      Serial.println("Couldn't find RTC");
      Serial.flush();
      while (1) delay(10);
    }

    if (! rtc.initialized() || rtc.lostPower()) {
      //Serial.println("RTC is NOT initialized, let's set the time!");
      //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    rtc.start();
    float drift = 43; // seconds plus or minus over oservation period - set to 0 to cancel previous calibration.
    float period_sec = (7 * 86400);  // total obsevation period in seconds (86400 = seconds in 1 day:  7 days = (7 * 86400) seconds )
    float deviation_ppm = (drift / period_sec * 1000000); //  deviation in parts per million (μs)
    float drift_unit = 4.34; // use with offset mode PCF8523_TwoHours
    int offset = round(deviation_ppm / drift_unit);
    //Serial.print("Offset is "); Serial.println(offset); // Print to control offset

    MedTime morningDrugAppt; morningDrugAppt.hour = 17; morningDrugAppt.minute = 40;drugAppointments[0] = morningDrugAppt;
    MedTime midDayDrugAppt; midDayDrugAppt.hour = 20; midDayDrugAppt.minute = 33;drugAppointments[1] = midDayDrugAppt;
    MedTime eveningDrugAppt; eveningDrugAppt.hour = 20; eveningDrugAppt.minute = 37;drugAppointments[2] = eveningDrugAppt;
}

void loopAlert () {
    alertPatient(drugAppointments, 20);
}

int getItemIndex(MedTime myTable[], int taille) {
  for(int i=0; i<taille; i++) {
    if(myTable[i].hour == 0 && myTable[i].minute == 0) {
      return i;
    }
  }
}

void addAppointment(MedTime myTable[], int taille, MedTime appointment) {
  int index = getItemIndex(myTable, taille);
  myTable[index] = appointment;
}

void alertPatient(MedTime myTable[], int taille) {
  int index = getItemIndex(myTable, taille);
  DateTime now = rtc.now();
  Serial.print(now.hour());Serial.print(":");Serial.println(now.minute());
  for(int i=0; i<index; i++) {
    if(myTable[i].hour == now.hour() && myTable[i].minute == (now.minute()+5)) {
      alert();
    }
  }
}

void alert() {
  digitalWrite(pinAudio, HIGH); // play audio message to alert the patient about his drug take time
}









