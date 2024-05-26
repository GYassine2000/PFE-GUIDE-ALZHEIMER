#ifndef httprequests_H
#define httprequests_H
#include <Arduino.h>

void parseATText(byte b);

void sendGSM(const char* msg, int waitMs = 500);

void resetBuffer();

void setupHTTP(String url, String apn);

void loopHTTP();


#endif