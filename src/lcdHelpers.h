#pragma once
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

namespace lcd {

    extern LiquidCrystal_I2C lcd;

    void initLCD();
    void displayMessage(const String& message);
    void displayTwoLines(const String& line1, const String& line2);
    void displayWiFiInfo(const String& ssid, const String& ip);

}