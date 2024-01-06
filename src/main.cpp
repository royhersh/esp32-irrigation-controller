#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include <WiFiManager.h> 

#include <NTPClient.h>
#include "SPIFFS.h"
#include "ESPAsyncWebServer.h"

// LCD
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// WiFI Manager
WiFiManager wifiManager; // global instance of the wifi manager
/**
 * gets called when WiFiManager enters configuration mode
 * Prints on the LCD the SSID and IP
*/
void configModeCallback (WiFiManager *myWiFiManager) {
  lcd.clear();
  lcd.print("SSID: "+myWiFiManager->getConfigPortalSSID());
  lcd.setCursor(0, 1);
  lcd.print(WiFi.softAPIP());
  Serial.println("IP:"+WiFi.softAPIP().toString()) ;
}
/**
 * gets called just before saving the config 
*/
void preSaveConfigCallback () {
  lcd.clear();
  lcd.print("Connecting . . .");
  Serial.println("Connecting . . .");
}

/**
 * gets called after config save and reboot
*/
void saveConfigCallback () {
  lcd.clear();
  lcd.print("SUCCESS");
  Serial.println("SUCCESS");
}

// Define the NTP settings
const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 2 * 60 * 60; // Israel timezone is UTC+2
const int daylightOffset_sec = 0;

// Define the NTP client
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, ntpServer, gmtOffset_sec, daylightOffset_sec);

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

void setup() {
  Serial.begin(9600);

  // Init LCD
  lcd.init();                      
  lcd.backlight(); // Turn on the backlight
  lcd.clear();
  lcd.print("Starting...");

  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Init WiFi Manager
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP 
  // wifiManager.resetSettings();
  wifiManager.setAPCallback(configModeCallback); 
  wifiManager.setSaveConfigCallback(saveConfigCallback);
  wifiManager.setPreSaveConfigCallback(preSaveConfigCallback);
  wifiManager.setSaveConnectTimeout(10);

  bool res;

  res = wifiManager.autoConnect("Irrigation"); 
  if(!res) {
    lcd.clear();
    lcd.print("Failed to connect");
    // ESP.restart();
  } 
  else {
    //if you get here you have connected to the WiFi 
    lcd.clear();
    lcd.print("Connected to WiFi");
    // Print ESP32 Local IP Address
    Serial.println(WiFi.localIP());

    // Connect to NTP server
    timeClient.begin();
    while (!timeClient.update())
    {
      timeClient.forceUpdate();
    }
    Serial.println(timeClient.getFormattedDate());

    // Async web server
    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
    server.begin();

  }
}

void loop() {
  lcd.clear();
  lcd.print("Nav to IP: ");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  delay(2000);

  timeClient.update();
  lcd.clear();
  lcd.print(timeClient.getFormattedDate());
  delay(2000);
}

