#pragma once
#include <WiFiManager.h> 
#include <LcdHelpers.h>
#include <Globals.h>

namespace wifi {
    extern WiFiManager wifiManager; // global instance of the wifi manager

    static void configModeCallback(WiFiManager *myWiFiManager);
    static void preSaveConfigCallback();
    static void saveConfigCallback();
    void initWifi();
    void resetWifiSettings();
}