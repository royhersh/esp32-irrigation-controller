#pragma once
#include <NTPClient.h>
#include <WiFiUdp.h>

// Define the NTP settings
extern const char *ntpServer;
extern const long gmtOffset_sec;
extern const int daylightOffset_sec;

namespace ntp {
    // Declare the NTP client and its methods
    extern WiFiUDP ntpUDP;
    extern NTPClient timeClient;

    String getFormattedDate();
    void initNTP();
}
