//- -----------------------------------------------------------------------------------------------------------------------
// NtpFunctions
// 2020-02-16 jp112sdl Creative Commons - http://creativecommons.org/licenses/by-nc-sa/3.0/de/
//- ---------

#ifndef NTPFUNCTIONS_H_
#define NTPFUNCTIONS_H_
#include "WiFiFunctions.h"
#include <NTPClientLib.h>

#define SHOW_TIME_PERIOD 5000
#define NTP_TIMEOUT      2500

int8_t timeZone = 1;
int8_t minutesTimeZone = 0;
const PROGMEM char *ntpServer = "pool.ntp.org";

boolean syncEventTriggered = false; // True if a time event has been triggered
NTPSyncEvent_t ntpEvent; // Last triggered event

void processSyncEvent (NTPSyncEvent_t ntpEvent) {
    if (ntpEvent < 0) {
        Serial.printf ("Time Sync error: %d\n", ntpEvent);
        if (ntpEvent == noResponse)
            Serial.println ("NTP server not reachable");
        else if (ntpEvent == invalidAddress)
            Serial.println ("Invalid NTP server address");
        else if (ntpEvent == errorSending)
            Serial.println ("Error sending request");
        else if (ntpEvent == responseError)
            Serial.println ("NTP response error");
    } else {
        if (ntpEvent == timeSyncd) {
            Serial.print ("Got NTP time: ");
            Serial.println (NTP.getTimeDateString (NTP.getLastNTPSync ()));
        }
    }
}

void setNTPSettings() {
  NTP.onNTPSyncEvent ([](NTPSyncEvent_t event) {
    ntpEvent = event;
    syncEventTriggered = true;
  });

  NTP.setInterval(3600);
  NTP.setNTPTimeout(NTP_TIMEOUT);
  NTP.begin(ntpServer, timeZone, true, minutesTimeZone);
}

void checkSyncEventTriggered() {
  if (syncEventTriggered) {
    processSyncEvent(ntpEvent);
    syncEventTriggered = false;
  }
}

#endif /* NTPFUNCTIONS_H_ */
