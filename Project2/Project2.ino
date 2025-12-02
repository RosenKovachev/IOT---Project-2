/******************************************************
 SMART LIGHT ALARM – CLEAN & STABLE VERSION
 Project 2: WiFi + Email via PushingBox
******************************************************/

#include <WiFiS3.h>
#include <WiFiClient.h>


char ssid[] = "LAN Solo";
char pass[] = "pishkinamaika";


String deviceID = "v350A1DE9AF19BF6";
const char serverName[] = "api.pushingbox.com";

WiFiClient client;

int lightPin  = A0;   // Light → A0
int buttonPin = D4;    // Button → D4
int buzzerPin = 5;    // Buzzer → D5

int lightLimit = 350;
unsigned long snoozeUntil = 0;
const unsigned long snoozeMs   = 15000; // 15 sec snooze
const unsigned long debounceMs = 200;


unsigned long lastPress = 0;
int lastButton = HIGH;
bool emailSent = false;
