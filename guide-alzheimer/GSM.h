#ifndef GSM_H
#define GSM_H
#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial GSM(3,2);

void setupGSM();

void loopGSM(float distance, bool issentSMS);

void sendSMS();

void updateSerial();

void calculateSendingSMS(float distance, bool issentSMS);

#endif