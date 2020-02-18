//#define DRY_RUN
#define LOGLEVEL 3

#include "printf_helper.h"
#include "Em7seg_cntrl.h"


DisplayWithSegmentModules<1> d;

void setup() {
  Serial.begin(57600);
  Serial.println("Start");
  d.init();
  d.clear();

  delay(1000);

  //Serial.println("======");
  //d.displayNumber(6);
  //Serial.println("======");
  //d.displayNumber(8);
  //Serial.println("======");

  for (uint8_t i = 0; i <10; i++) {
      d.displayNumber(i);
  //  d.displaySingleDigit(1, i);
    delay(1000);
  }

}


void loop() {


}
