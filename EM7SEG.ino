#define LOGLEVEL 0

#include "printf_helper.h"
#include "Em7seg_cntrl.h"


DisplayWithSegmentModules d;

void setup() {
  Serial.begin(57600);
  Serial.println("Start");
  d.init();
  d.clear();

  delay(500);
  d.round_cw();
  d.round_cw();
  delay(500);

  for (uint8_t j = 0; j < 5; j++) {
    for (uint8_t i = 0; i <10; i++) {
      d.displayNumber(i);
      delay((j*100)+50);
    }
  }

  d.displayNumber(0);

}


void loop() {


}
