//- -----------------------------------------------------------------------------------------------------------------------
// Dcf77
// 2020-02-21 jp112sdl Creative Commons - http://creativecommons.org/licenses/by-nc-sa/3.0/de/
//- -----------------------------------------------------------------------------------------------------------------------

/*
  DCF77.c - DCF77 library
  Copyright (c) Thijs Elenbaas 2012

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/


#ifndef DCF77_H_
#define DCF77_H_

#include <Time.h>        //http://playground.arduino.cc/code/time
#include "Arduino.h"

#define MIN_TIME 1334102400     // Date: 11-4-2012
#define MAX_TIME 4102444800     // Date:  1-1-2100

#define DCFRejectionTime 700    // Pulse-to-Pulse rejection time.
#define DCFRejectPulseWidth 50  // Minimal pulse width
#define DCFSplitTime 180        // Specifications distinguishes pulse width 100 ms and 200 ms. In practice we see 130 ms and 230
#define DCFSyncTime 1500        // Specifications defines 2000 ms pulse for end of sequence

class DCF77 {
private:
  //Private variables
  bool initialized;
  static int dCF77Pin;
  static int dCFBlinkPin;
  static int dCFinterrupt;
  static uint8_t pulseStart;

  // DCF77 and internal timestamps
  static time_t previousUpdatedTime;
  static time_t latestupdatedTime;
  static  time_t processingTimestamp;
  static  time_t previousProcessingTimestamp;
  static unsigned char CEST;
  // DCF time format structure
  struct DCF77Buffer {
    //unsigned long long prefix       :21;
    unsigned long long prefix     :17;
    unsigned long long CEST       :1; // CEST
    unsigned long long CET        :1; // CET
    unsigned long long unused     :2; // unused bits
    unsigned long long Min        :7; // minutes
    unsigned long long P1         :1; // parity minutes
    unsigned long long Hour       :6; // hours
    unsigned long long P2         :1; // parity hours
    unsigned long long Day        :6; // day
    unsigned long long Weekday    :3; // day of week
    unsigned long long Month      :5; // month
    unsigned long long Year       :8; // year (5 -> 2005)
    unsigned long long P3         :1; // parity
  };


  // DCF Parity format structure
  struct ParityFlags{
      unsigned char parityFlag    :1;
      unsigned char parityMin     :1;
      unsigned char parityHour    :1;
      unsigned char parityDate    :1;
  } static flags;

  // Parameters shared between interupt loop and main loop
  static volatile bool FilledBufferAvailable;
  static volatile unsigned long long filledBuffer;
  static volatile time_t filledTimestamp;

  // DCF Buffers and indicators
  static int  bufferPosition;
  static unsigned long long runningBuffer;
  static unsigned long long processingBuffer;

  // Pulse flanks
  static   int  leadingEdge;
  static   int  trailingEdge;
  static   int  PreviousLeadingEdge;
  static   bool Up;

/**
 * Initialize parameters
 */
void initialize(uint8_t DCF_PIN, uint8_t DCF_INTERRUPT, uint8_t DCF_BLINK_PIN, bool OnRisingFlank = true) {
  dCF77Pin              = DCF_PIN;
  dCFinterrupt          = DCF_INTERRUPT;
  dCFBlinkPin           = DCF_BLINK_PIN;
  leadingEdge           = 0;
  trailingEdge          = 0;
  PreviousLeadingEdge   = 0;
  Up                    = false;
  runningBuffer         = 0;
  FilledBufferAvailable = false;
  bufferPosition        = 0;
  flags.parityDate      = 0;
  flags.parityFlag      = 0;
  flags.parityHour      = 0;
  flags.parityMin       = 0;
  CEST                  = 0;

  pulseStart   = OnRisingFlank ? HIGH : LOW;
  pinMode(dCF77Pin, INPUT);
  pinMode(dCFBlinkPin, OUTPUT);
}


/**
 * Add new bit to buffer
 */
inline static void appendSignal(unsigned char signal) {
#if LOGLEVEL > 2
  Serial.print(signal, DEC);
#endif
  runningBuffer = runningBuffer | ((unsigned long long) signal << bufferPosition);
  bufferPosition++;
  if (bufferPosition > 59) {
    // Buffer is full before at end of time-sequence
    // this may be due to noise giving additional peaks
#if LOGLEVEL > 2
    Serial.println("EoB");
#endif
    finalizeBuffer();
  }
}

/**
 * Finalize filled buffer
 */
inline static void finalizeBuffer() {
  if (bufferPosition == 59) {
    // Buffer is full
#if LOGLEVEL > 2
    Serial.println("BF");
#endif
    // Prepare filled buffer and time stamp for main loop
    filledBuffer = runningBuffer;
    filledTimestamp = now();
    // Reset running buffer
    bufferinit();
    FilledBufferAvailable = true;
    } else {
    // Buffer is not yet full at end of time-sequence
#if LOGLEVEL > 2
    Serial.println("EoM");
#endif
    // Reset running buffer
    bufferinit();
    }
}

/**
 * Returns whether there is a new time update available
 * This functions should be called prior to getTime() function.
 */
bool receivedTimeUpdate() {
  // If buffer is not filled, there is no new time
  if(!FilledBufferAvailable) {
    return false;
  }
  // if buffer is filled, we will process it and see if this results in valid parity
  if (!processBuffer()) {
#if LOGLEVEL > 2
    Serial.println("Invalid parity");
#endif
    return false;
  }

  // Since the received signal is error-prone, and the parity check is not very strong,
  // we will do some sanity checks on the time
  time_t processedTime = latestupdatedTime + (now() - processingTimestamp);
  if (processedTime<MIN_TIME || processedTime>MAX_TIME) {
#if LOGLEVEL > 2
    Serial.println("Time outside of bounds");
#endif
    return false;
  }

  // If received time is close to internal clock (2 min) we are satisfied
  time_t difference = abs(processedTime - now());
  if(difference < 2*SECS_PER_MIN) {
#if LOGLEVEL > 2
    Serial.println("close to internal clock");
#endif
    storePreviousTime();
    return true;
  }

  // Time can be further from internal clock for several reasons
  // We will check if lag from internal clock is consistent
  time_t shiftPrevious = (previousUpdatedTime - previousProcessingTimestamp);
  time_t shiftCurrent = (latestupdatedTime - processingTimestamp);
  time_t shiftDifference = abs(shiftCurrent-shiftPrevious);
  storePreviousTime();
  if(shiftDifference < 2*SECS_PER_MIN) {
#if LOGLEVEL > 2
    Serial.println("time lag consistent");
#endif
    return true;
  } else {
#if LOGLEVEL > 2
    Serial.println("time lag inconsistent");
#endif
  }

  // If lag is inconsistent, this may be because of no previous stored date
  // This would be resolved in a second run.
  return false;
}

/**
 * Store previous time. Needed for consistency
 */
void storePreviousTime() {
  previousUpdatedTime = latestupdatedTime;
  previousProcessingTimestamp = processingTimestamp;
}

/**
 * Calculate the parity of the time and date.
 */
void calculateBufferParities() {
  // Calculate Parity
  flags.parityFlag = 0;
  for(int pos=0;pos<59;pos++) {
    bool s = (processingBuffer >> pos) & 1;

    // Update the parity bits. First: Reset when minute, hour or date starts.
    if (pos ==  21 || pos ==  29 || pos ==  36) {
      flags.parityFlag = 0;
    }
    // save the parity when the corresponding segment ends
    if (pos ==  28) {flags.parityMin = flags.parityFlag;};
    if (pos ==  35) {flags.parityHour = flags.parityFlag;};
    if (pos ==  58) {flags.parityDate = flags.parityFlag;};
    // When we received a 1, toggle the parity flag
    if (s == 1) {
      flags.parityFlag = flags.parityFlag ^ 1;
    }
  }
}

/**
 * Evaluates the information stored in the buffer. This is where the DCF77
 * signal is decoded
 */
bool processBuffer() {

  /////  Start interaction with interrupt driven loop  /////

  // Copy filled buffer and timestamp from interrupt driven loop
  processingBuffer = filledBuffer;
  processingTimestamp = filledTimestamp;
  // Indicate that there is no filled, unprocessed buffer anymore
  FilledBufferAvailable = false;

  /////  End interaction with interrupt driven loop   /////

  //  Calculate parities for checking buffer
  calculateBufferParities();
  tmElements_t time;

  struct DCF77Buffer *rx_buffer;
  rx_buffer = (struct DCF77Buffer *)(unsigned long long)&processingBuffer;

  // Check parities
    if (flags.parityMin == rx_buffer->P1  &&
        flags.parityHour == rx_buffer->P2 &&
        flags.parityDate == rx_buffer->P3 &&
    rx_buffer->CEST != rx_buffer->CET)
    {
      //convert the received buffer into time
      time.Second = 0;
      time.Minute = rx_buffer->Min-((rx_buffer->Min/16)*6);
      time.Hour   = rx_buffer->Hour-((rx_buffer->Hour/16)*6);
      time.Day    = rx_buffer->Day-((rx_buffer->Day/16)*6);
      time.Month  = rx_buffer->Month-((rx_buffer->Month/16)*6);
      time.Year   = 2000 + rx_buffer->Year-((rx_buffer->Year/16)*6) -1970;
    latestupdatedTime = makeTime(time);
    CEST = rx_buffer->CEST;
    //Parity correct
    return true;
  } else {
    //Parity incorrect
    return false;
  }
}

/**
 * Initialize buffer for next time update
 */
inline static void bufferinit() {
  runningBuffer    = 0;
  bufferPosition   = 0;
}

/**
 * Interrupt handler that processes up-down flanks into pulses and stores these in the buffer
 */
static void int0handler() {
  int flankTime = millis();
  uint8_t sensorValue = digitalRead(dCF77Pin);

  // If flank is detected quickly after previous flank up
  // this will be an incorrect pulse that we shall reject
  if ((flankTime-PreviousLeadingEdge)<DCFRejectionTime) {
#if LOGLEVEL > 2
    Serial.println("rCT");
#endif
    return;
  }

  // If the detected pulse is too short it will be an
  // incorrect pulse that we shall reject as well
  if ((flankTime-leadingEdge)<DCFRejectPulseWidth) {
#if LOGLEVEL > 2
      Serial.println("rPW");
#endif
    return;
  }

  if(sensorValue==pulseStart) {
    if (!Up) {
      // Flank up
      leadingEdge=flankTime;
      Up = true;
    }
  } else {
    if (Up) {
      // Flank down
      trailingEdge=flankTime;
      int difference=trailingEdge - leadingEdge;

      if ((leadingEdge-PreviousLeadingEdge) > DCFSyncTime) {
        finalizeBuffer();
      }
      PreviousLeadingEdge = leadingEdge;
      // Distinguish between long and short pulses
      if (difference < DCFSplitTime) { appendSignal(0); } else { appendSignal(1); }
      Up = false;
    }
  }
  digitalWrite(dCFBlinkPin, Up);
}

public:

/**
 * Get most recently received time
 * Note, this only returns an time once, until the next update
 */
time_t getTime() {
  if (!receivedTimeUpdate()) {
    return(0);
  } else {
    // Send out time, taking into account the difference between when the DCF time was received and the current time
    time_t currentTime =latestupdatedTime + (now() - processingTimestamp);
    return(currentTime);
  }
}

/**
 * Get most recently received time in UTC
 * Note, this only returns an time once, until the next update
 */
time_t getUTCTime() {
  if (!receivedTimeUpdate()) {
    return(0);
  } else {
    // Send out time UTC time
    int UTCTimeDifference = (CEST ? 2 : 1)*SECS_PER_HOUR;
    time_t currentTime =latestupdatedTime - UTCTimeDifference + (now() - processingTimestamp);
    return(currentTime);
  }
}

/**
 * Start receiving DCF77 information
 */
void Start(uint8_t DCF_PIN, uint8_t DCF_INTERRUPT, uint8_t DCF_BLINK_PIN) {
  initialize(DCF_PIN, DCF_INTERRUPT, DCF_BLINK_PIN);
  attachInterrupt(dCFinterrupt, int0handler, CHANGE);
}

void Stop() {
  detachInterrupt(dCFinterrupt);
}

};


#endif /* DCF77_H_ */
