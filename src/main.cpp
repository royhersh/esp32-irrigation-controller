#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include <WiFiManager.h> 

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


void setup() {
  Serial.begin(9600);

  // Init LCD
  lcd.init();                      
  lcd.backlight(); // Turn on the backlight

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
    lcd.print("connected...yeey :)");
  }
}

void loop() {


}

