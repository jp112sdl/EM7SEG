#define LOGLEVEL 0
#define DCF_TEST

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

  delay(500);

#ifdef DCF_TEST
  pinMode(DCF_PIN, INPUT);
  Serial.println("Beginne DCF77 Messung, bitte warten :");
  //Ein schlechter Empfang bedeutet nicht das wir kein Empfang haben, nur das es länger dauern würde
  //das Signal auszuwerten.
  Serial.println("KEIN SIGNAL <- |                                          <- MISERABEL <- |  SCHLECHT <- |          GUT          | -> SCHLECHT  | -> MISERABEL ->");

#else
  DCF.Start(DCF_PIN, DCF_INTERRUPT, DCF_BLINK_PIN);

  setSyncInterval(30);
  setSyncProvider(getDCFTime);
  // It is also possible to directly use DCF.getTime, but this function gives a bit of feedback
  //setSyncProvider(DCF.getTime);

  Serial.println("Waiting for DCF77 time ... ");
  Serial.println("It will take at least 2 minutes until a first update can be processed.");
  uint8_t b = 1;
  while(timeStatus()== timeNotSet) {
      //d.showSegments(0,b);
      b=b*2;
      if (b==64) b=1;
     Serial.print(".");
     delay(2000);
  }
  d.displaySingleDigit(0, 5);
#endif

}

unsigned long getDCFTime() {
  time_t DCFtime = DCF.getTime();
  // Indicator that a time check is done
  if (DCFtime!=0) {
    Serial.println("Time set for syncProvider success");
  }
  return DCFtime;
}


int DCF77signalQuality(int pulses) {
  int prevSensorValue=0;
  unsigned long loopTime = 10000; //Impuls Länge genau eine Sekunde
  //Da wir ja mitten in einem Impuls einsteigen könnten, verwerfen wir den ersten.
  int rounds = -1;
  unsigned long gagingStart = 0;
  unsigned long waitingPeriod = 0;
  int overallChange = 0;
  int change = 0;

  while (true) {
    //Unsere Schleife soll das Eingangssignal (LOW oder HIGH) 10 mal pro
    //Sekunde messen um das sicherzustellen, messen wir dessen Ausführungszeit.
    gagingStart = micros();
    int sensorValue = digitalRead(DCF_PIN);
    //Wenn von LOW nach HIGH gewechselt wird beginnt ein neuer Impuls
    if (sensorValue==1 && prevSensorValue==0) {
      rounds++;
      if (rounds > 0 && rounds < pulses + 1) {overallChange+= change;}
      if (rounds == pulses) { return overallChange /pulses;}
      change = 0;
    }
    prevSensorValue = sensorValue;
    change++;

    //Ein Wechsel zwichen LOW und HIGH müsste genau alle 100 Durchläufe stattfinden
    //wird er größer haben wir kein Empfang
    //300 habe ich als guten Wert ermittelt, ein höherer Wert würde die Aussage festigen
    //erhöht dann aber die Zeit.
    if (change > 300) {return 0;}
    //Berechnen und anpassen der Ausführungszeit
    waitingPeriod = loopTime - (micros() - gagingStart);
    delayMicroseconds(waitingPeriod);
  }
}

void loop() {
#ifdef DCF_TEST
  //Führe eine Messung über 10 Impulse aus, ein Impuls dauert genau eine Sekunde
  int q = DCF77signalQuality(10);
  //Wenn kein Wechsel zwischen HIGH und LOW am Anschluss erkannt wurde
  //bedeutet das in 99,99% aller Fälle das der DCF Empfänger nicht arbeitet
  //denn bei extrem schlechten Empfang hat man Wechsel, nur kann man sie nicht auswerten.
  if (!q) {Serial.print("# (Schaltung pruefen!)");}
  for (int i = 0; i < q; i++) {
    Serial.print(">");
  }
  Serial.println("");
#else
  if( now() != prevDisplay) //update the display only if the time has changed
  {
    prevDisplay = now();
    p("%02d:%02d:%02d %02d.%02d.%d \n", hour(), minute(), second(), day(), month(), year());
  }
#endif
}
