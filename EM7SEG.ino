#define LOGLEVEL 0

#include <ArduinoOTA.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266WebServer.h>


#include "printf_helper.h"
#include "Em7seg_cntrl.h"
EM7ModuleArray d;

#include "WiFiFunctions.h"
#include "NtpFunctions.h"

#define ENABLE_PIN D7

      uint8_t lastMinute = 0;
      uint8_t lastHour   = 0;
const uint16_t segDly    = 60;
const char * host = "em7segclock";


ESP8266WebServer server(80);
ESP8266HTTPUpdateServer httpUpdater;

void startOTAhandling() {
  Serial.print(F("Starte OTA-Handler... "));
  ArduinoOTA.onStart([]() {
    Serial.println(F("Start updating"));
  });
  ArduinoOTA.onEnd([]() {
    Serial.print("\nEnd");
  });
  ArduinoOTA.onProgress([](__attribute__ ((unused))unsigned int progress,__attribute__ ((unused)) unsigned int total) {
    Serial.print(".");
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.print("Error "+String(error));
    if (error == OTA_AUTH_ERROR) Serial.print("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.print("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.print("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.print("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.print("End Failed");
  });

  ArduinoOTA.setHostname(host);
  ArduinoOTA.begin();
  Serial.println("done");
}

void rotateAnimation() {
  d.showSegments(4, 0b00010000);
  d.showSegments(4, 0b00110000);
  d.showSegments(4, 0b00110001);
  d.showSegments(3, 0b00000001);
  d.showSegments(2, 0b00000001);
  d.showSegments(1, 0b00000001);
  d.showSegments(1, 0b00000011);
  d.showSegments(1, 0b00000111);
  d.showSegments(1, 0b00001111);
  d.showSegments(2, 0b00001001);
  d.showSegments(3, 0b00001001);
  d.showSegments(4, 0b00111001);

  d.showSegments(4, 0b00101001);
  d.showSegments(4, 0b00001001);
  d.showSegments(4, 0b00001000);
  d.showSegments(3, 0b00001000);
  d.showSegments(2, 0b00001000);
  d.showSegments(1, 0b00001110);
  d.showSegments(1, 0b00001100);
  d.showSegments(1, 0b00001000);
  d.showSegments(1, 0b00000000);
  d.showSegments(2, 0b00000000);
  d.showSegments(3, 0b00000000);
  d.showSegments(4, 0b00000000);
}

void setup() {
  Serial.begin(57600);
  Serial.println("Start");
  uint8_t moduleCount = d.init(ENABLE_PIN);
  if (moduleCount == 0) {
    delay(1000);
    ESP.restart();
  }

  d.setSegToSegDelayMillis(10);

  doWifiConnect();
  setNTPSettings();

  d.setSegToSegDelayMillis(segDly);

  MDNS.begin(host);

  startOTAhandling();

  httpUpdater.setup(&server);

  server.begin();
}

void showtime(uint8_t h, uint8_t m) {
  uint16_t t = ((h*100)+m);
  p("%01d\n",t);
  d.displayNumber(t, true);
}

void loop() {
  checkSyncEventTriggered();
  ArduinoOTA.handle();
  server.handleClient();

  uint8_t h = hour();
  uint8_t m = minute();

  //do a nice rotation animation every hour
  if (lastHour != h) {
    lastHour = h;

    d.clear();

    d.setSegToSegDelayMillis(segDly / 2);
    for (uint8_t i = 0; i < 2; i++) {
      rotateAnimation();
    }
    d.setSegToSegDelayMillis(segDly);

    delay(300);

    showtime(h, m);

    lastMinute = m;
  }
  //if minute changes, refresh display
  else if (lastMinute != m) {
    lastMinute = m;
    showtime(h, m);
  }

  delay(0);
}
