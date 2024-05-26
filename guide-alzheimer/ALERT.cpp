#include "HardwareSerial.h"
#include "ALERT.h"
#include "mp3tf16p.h"

MP3Player mp3(10,11);

RTC_PCF8523 rtc;
MedTime drugAppointments[1];

void setupClock () {
  mp3.initialize();
  #ifndef ESP8266
    while (!Serial); // wait for serial port to connect. Needed for native USB
  #endif

    if (! rtc.begin()) {
      Serial.println("Couldn't find RTC");
      Serial.flush();
      while (1) delay(10);
    }

    if (! rtc.initialized() || rtc.lostPower()) {
      Serial.println("RTC is NOT initialized, let's set the time!");
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    rtc.start();
    float drift = 43; // seconds plus or minus over oservation period - set to 0 to cancel previous calibration.
    float period_sec = (7 * 86400);  // total obsevation period in seconds (86400 = seconds in 1 day:  7 days = (7 * 86400) seconds )
    float deviation_ppm = (drift / period_sec * 1000000); //  deviation in parts per million (μs)
    float drift_unit = 4.34; // use with offset mode PCF8523_TwoHours
    int offset = round(deviation_ppm / drift_unit);

    MedTime morningDrugAppt; morningDrugAppt.hour = 3; morningDrugAppt.minute = 8;drugAppointments[0] = morningDrugAppt;
}

void loopHorloge () {
  alertPatient(drugAppointments, 1);
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
  DateTime now = rtc.now();
  Serial.print("L'heure venant du module horloge: ");Serial.print(now.hour() + 1);Serial.print(":");Serial.println(now.minute());
  delay(300);
  for(int i=0; i<1; i++) {
    if(myTable[i].hour == now.hour() && myTable[i].minute == (now.minute())) {
      alert();
    }
  }
}

void alert() {
  mp3.playTrackNumber(1, 30);
  delay(20*1000);
}









