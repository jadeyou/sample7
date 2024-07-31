#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Set these to run example.
#define FIREBASE_HOST "sample4-2ae57-default-rtdb.firebaseio.com" // e.g. your_project.firebaseio.com
#define FIREBASE_AUTH "lTE8cowqM5kErKp1Ce5yrpRvXLKMb28Kc62eFBQ2" // Your database secret
#define WIFI_SSID "Sjie"
#define WIFI_PASSWORD "sjie2002"

FirebaseData firebaseData;
const int ledPin = D4; // GPIO2 (D4) on most ESP8266 boards

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (Firebase.getInt(firebaseData, "/LED_Status")) {
    if (firebaseData.dataType() == "int") {
      int ledStatus = firebaseData.intData();
      digitalWrite(ledPin, ledStatus);
    }
  }
  delay(1000); // Read data every second
}
