#include <Globals.h>
#include <LcdHelpers.h>
#include <WiFiHelpers.h>
#include <NtpHelpers.h>

#include "SPIFFS.h"
#include "ESPAsyncWebServer.h"


// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing...");

  // Init LCD
  lcd::initLCD();                      

  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  wifi::initWifi();

  //if you get here you have connected to the WiFi 
  lcd::displayMessage("Connected to WiFi");
  Serial.println("Connected to WiFi");
  
  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  ntp::initNTP();

  // Async web server
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
  server.begin();

  lcd::displayTwoLines("Nav to IP: ", WiFi.localIP().toString());
}

void loop() {
  lcd::displayTwoLines("Nav to IP: ", WiFi.localIP().toString());
  delay(2000);

  lcd::displayMessage(ntp::getFormattedDate());
  delay(2000);
}

