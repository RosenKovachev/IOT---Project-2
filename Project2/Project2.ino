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

void sendToPushingBox(int lightValue) {
  Serial.print("Sending to PushingBox... ");

  if (client.connect(serverName, 80)) {
    Serial.println("Connected!");

    String url = "/pushingbox?devid=" + deviceID + "&light=" + String(lightValue);

    client.println("GET " + url + " HTTP/1.1");
    client.println("Host: api.pushingbox.com");
    client.println("Connection: close");
    client.println();
  } else {
    Serial.println("FAILED to connect.");
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nWiFi Connected!");
}
void loop() {

  int lightValue = analogRead(lightPin);
  int buttonValue = digitalRead(buttonPin);
  unsigned long now = millis();

  // --- BUTTON PRESS (Active LOW) ---
  if (lastButton == HIGH && buttonValue == LOW && (now - lastPress) > debounceMs) {
    snoozeUntil = now + snoozeMs;
    lastPress = now;
    Serial.println(">>> SNOOZE FOR 15 SECONDS <<<");
  }

