#ifndef GSM_H
#define GSM_H
#include <Arduino.h>

void setupGSM();

void loopGSM(float distance, bool issentSMS);

void sendSMS();

void updateSerial();

void calculateSendingSMS(float distance, bool issentSMS);

#endif