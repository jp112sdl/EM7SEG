//- -----------------------------------------------------------------------------------------------------------------------
// NtpFunctions
// 2020-02-16 jp112sdl Creative Commons - http://creativecommons.org/licenses/by-nc-sa/3.0/de/
//- ---------

#ifndef WIFIFUNCTIONS_H_
#define WIFIFUNCTIONS_H_
#include "secrets.h"
#include <ESP8266WiFi.h>

String IpAddress2String(const IPAddress& ipAddress) {
  return String(ipAddress[0]) + String(".") + \
         String(ipAddress[1]) + String(".") + \
         String(ipAddress[2]) + String(".") + \
         String(ipAddress[3]);
}

void printWifiStatus() {
  Serial.println("MAC: " + WiFi.macAddress());
  Serial.println("SSID: " + WiFi.SSID());
  Serial.println("IP Address: " + IpAddress2String(WiFi.localIP()));
  Serial.println("Gateway Address: " + IpAddress2String(WiFi.gatewayIP()));
  Serial.println("signal strength (RSSI):" + String(WiFi.RSSI()) + " dBm");
}

void doWifiConnect() {
  Serial.print("Connecting WLAN...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, key);
  int waitCounter = 0;
  //WiFi.config(IPAddress(192, 168, 1, 17), IPAddress(192, 168, 1, 1), IPAddress(255, 255, 255, 0), IPAddress(192, 168, 1, 1));
  uint8_t b = 1;
  while (WiFi.status() != WL_CONNECTED) {
    waitCounter++;
    Serial.print(".");
    b = b*2;
    if (b==64) b= 1;
    d.showSegments(1,b);
    if (waitCounter == 20) {
      ESP.restart();
    }
    delay(500);
  }
  Serial.println("Wifi Connected");
  printWifiStatus();

}

#endif /* WIFIFUNCTIONS_H_ */
