#define LOGLEVEL 0

#include "printf_helper.h"
#include "Em7seg_cntrl.h"
EM7ModuleArray d;

#include "WiFiFunctions.h"
#include "NtpFunctions.h"


void setup() {
  Serial.begin(57600);
  Serial.println("Start");
  d.init();
  d.clear();

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  doWifiConnect();
  setNTPSettings();
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  checkSyncEventTriggered();

  if (lastSecond != second()) {
    p("%01d%01d\n",hour(),minute());

    uint8_t s = second();
    for (uint8_t i = 0; i < 6; i++) {
      if (s >= 10) s -= 10;
    }
    d.displaySingleDigit(1, s);
    lastSecond = second();
  }

  delay(0);
}
