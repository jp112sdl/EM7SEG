//- -----------------------------------------------------------------------------------------------------------------------
// printf_helper
// 2020-02-16 jp112sdl Creative Commons - http://creativecommons.org/licenses/by-nc-sa/3.0/de/
//- -----------------------------------------------------------------------------------------------------------------------

#ifndef PRINTF_HELPER_H_
#define PRINTF_HELPER_H_

#include <stdarg.h>

void p(const char *fmt, ... ){
        char buf[256]; // resulting string limited to 128 chars
        va_list args;
        va_start (args, fmt );
        vsnprintf(buf, 256, fmt, args);
        va_end (args);
        Serial.print(buf);
}

void pf(const __FlashStringHelper *fmt, ... ){
  char buf[256]; // resulting string limited to 128 chars
  va_list args;
  va_start (args, fmt);
#ifdef __AVR__
  vsnprintf_P(buf, sizeof(buf), (const char *)fmt, args); // progmem for AVR
#else
  vsnprintf(buf, sizeof(buf), (const char *)fmt, args); // for the rest of the world
#endif
  va_end(args);
  Serial.print(buf);
}
#endif /* PRINTF_HELPER_H_ */
