#include <NtpHelpers.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// Define the NTP settings
const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 2 * 60 * 60; // Israel timezone is UTC+2
const int daylightOffset_sec = 0;

namespace ntp {
    // Define the NTP client
    WiFiUDP ntpUDP;
    NTPClient timeClient(ntpUDP, ntpServer, gmtOffset_sec, daylightOffset_sec);

    String getFormattedDate() {
        timeClient.update();
        return timeClient.getFormattedDate();
    }

    void initNTP() {
        Serial.println("Connecting to NTP server...");
        timeClient.begin();
        while (!timeClient.update())
        {
            timeClient.forceUpdate();
        }
        Serial.println("Connected to NTP server");
        Serial.println(getFormattedDate());
    }


}