#include <WiFiHelpers.h>
#include <WiFiManager.h> 
#include <LcdHelpers.h>
#include <Globals.h>

namespace wifi {
    WiFiManager wifiManager; // global instance of the wifi manager

    /**
     * gets called when WiFiManager enters configuration mode
     * Prints on the LCD the SSID and IP
    */
    static void configModeCallback (WiFiManager *myWiFiManager) {
        lcd::displayWiFiInfo(myWiFiManager->getConfigPortalSSID(), WiFi.softAPIP().toString());
        Serial.println("IP:"+WiFi.softAPIP().toString()) ;
    }
    
    /**
     * gets called just before saving the config 
    */
    static void preSaveConfigCallback () {
        lcd::displayMessage("Connecting . . .");
        Serial.println("Connecting . . .");
    }

    /**
     * gets called after config save and reboot
    */
    static void saveConfigCallback () {
        lcd::displayMessage("SUCEESS");
        Serial.println("SUCCESS");
    }

    void initWifi() {
        WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP 
        wifiManager.setAPCallback(configModeCallback); 
        wifiManager.setSaveConfigCallback(saveConfigCallback);
        wifiManager.setPreSaveConfigCallback(preSaveConfigCallback);
        wifiManager.setSaveConnectTimeout(10);

        bool res;

        res = wifiManager.autoConnect(config::SSID);   
        
        if(!res) {
            lcd::displayMessage("Failed to connect");
            Serial.println("Failed to connect");
            Serial.println("Restarting in 10 seconds");
            delay(10000);
            ESP.restart();
        } 
        
    }

    void resetWifiSettings() {
        wifiManager.resetSettings();
    }

}