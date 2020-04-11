#define LOGLEVEL 0

#include "printf_helper.h"
#include "Em7seg_cntrl.h"
EM7ModuleArray d;

#include "WiFiFunctions.h"
#include "NtpFunctions.h"

uint8_t lastMinute;

void setup() {
  Serial.begin(57600);
  Serial.println("Start");
  uint8_t moduleCount = d.init();
  if (moduleCount == 0) {
    ESP.restart();
  }
  d.clear();
  delay(200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  doWifiConnect();
  setNTPSettings();
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  checkSyncEventTriggered();

  if (lastMinute != minute()) {
    lastMinute = minute();
    uint16_t t = (hour()*100)+minute();
    p("%01d\n",t);
    d.displayNumber(t, true);
  }

  delay(0);
}
