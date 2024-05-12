#ifndef ALERT_H
#define ALERT_H
#include <Arduino.h>

struct MedTime {
  int hour;
  int minute;
};

void setupClock ();

void loopAlert ();

int getItemIndex(MedTime myTable[], int taille);

void addAppointment(MedTime myTable[], int taille, MedTime appointment);

void alertPatient(MedTime myTable[], int taille);

void alert();


#endif