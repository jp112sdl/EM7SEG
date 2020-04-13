#define LOGLEVEL 0

#include "printf_helper.h"
#include "Em7seg_cntrl.h"
EM7ModuleArray d;

#include "WiFiFunctions.h"
#include "NtpFunctions.h"

#define ENABLE_PIN D7

uint8_t lastMinute;
uint8_t lastHour;
const uint16_t segDly = 60;

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
}

void loop() {
  checkSyncEventTriggered();

  if (lastHour != hour()) {
    d.clear();

    d.setSegToSegDelayMillis(segDly / 2);

    for (uint8_t i = 0; i < 2; i++) {
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

    delay(500);
    d.setSegToSegDelayMillis(segDly);

    lastHour = hour();
  }

  if (lastMinute != minute()) {
    lastMinute = minute();
    uint16_t t = (hour()*100)+minute();
    p("%01d\n",t);
    d.displayNumber(t, true);
  }

  delay(0);
}
