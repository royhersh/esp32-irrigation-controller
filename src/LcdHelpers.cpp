#include <LcdHelpers.h>
#include <LiquidCrystal_I2C.h>


namespace lcd {

    LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

    void initLCD() {
        lcd.init();
        lcd.backlight(); // Turn on the backlight
        lcd.clear();
        lcd.print("Starting...");
    }

    void displayMessage(const String& message) {
        lcd.clear();
        lcd.print(message);
    }

    void displayTwoLines(const String& line1, const String& line2) {
        lcd.clear();
        lcd.print(line1);
        lcd.setCursor(0, 1);
        lcd.print(line2);
    }

    void displayWiFiInfo(const String& ssid, const String& ip) {
        lcd.clear();
        lcd.print("SSID: " + ssid);
        lcd.setCursor(0, 1);
        lcd.print(ip);
    }

}