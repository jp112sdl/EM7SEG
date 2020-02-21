#define LOGLEVEL 0

#include "printf_helper.h"
#include "Em7seg_cntrl.h"
#include "Dcf77.h"

#define DCF_PIN       2    // Connection pin to DCF 77 device
#define DCF_INTERRUPT 0    // Interrupt number associated with pin
#define DCF_BLINK_PIN 4
DCF77 DCF;
EM7ModuleArray d;

time_t prevDisplay = 0;          // when the digital clock was displayed

void setup() {
  Serial.begin(57600);
  Serial.println("Start");
  d.init();
  d.clear();
/*
  delay(500);
  d.round_cw();
  d.round_cw();
  d.round_cw();

  for (uint8_t j = 0; j < 3; j++) {
    for (uint8_t i = 0; i <10; i++) {
      d.displayNumber(i);
      delay((j*100)+50);
    }
  }

  */
  d.displayNumber(0);

  DCF.Start(DCF_PIN, DCF_INTERRUPT, DCF_BLINK_PIN);

  setSyncInterval(30);
  setSyncProvider(getDCFTime);
  // It is also possible to directly use DCF.getTime, but this function gives a bit of feedback
  //setSyncProvider(DCF.getTime);

  Serial.println("Waiting for DCF77 time ... ");
  Serial.println("It will take at least 2 minutes until a first update can be processed.");
  while(timeStatus()== timeNotSet) {
     // wait until the time is set by the sync provider
     Serial.print(".");
     delay(2000);
  }

}



void digitalClockDisplay(){
  p("%d:%d:%d %d:%d:%d \n", hour(), minute(), second(), day(), month(), year());

}


unsigned long getDCFTime() {
  time_t DCFtime = DCF.getTime();
  // Indicator that a time check is done
  if (DCFtime!=0) {
    Serial.print("X");
  }
  return DCFtime;
}

void loop() {
  if( now() != prevDisplay) //update the display only if the time has changed
  {
    prevDisplay = now();
    digitalClockDisplay();
  }

}
