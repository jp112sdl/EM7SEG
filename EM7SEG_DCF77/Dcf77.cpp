//- -----------------------------------------------------------------------------------------------------------------------
// Dcf77
// 2020-02-21 jp112sdl Creative Commons - http://creativecommons.org/licenses/by-nc-sa/3.0/de/
//- -----------------------------------------------------------------------------------------------------------------------


#include "Dcf77.h"

int DCF77::dCF77Pin=0;
int DCF77::dCFBlinkPin=0;
int DCF77::dCFinterrupt=0;
uint8_t DCF77::pulseStart=1;
volatile unsigned long long DCF77::filledBuffer = 0;
volatile bool DCF77::FilledBufferAvailable= false;
volatile time_t DCF77::filledTimestamp= 0;

// DCF Buffers and indicators
int DCF77::bufferPosition = 0;
unsigned long long DCF77::runningBuffer = 0;
unsigned long long DCF77::processingBuffer = 0;

// Pulse flanks
int DCF77::leadingEdge=0;
int DCF77::trailingEdge=0;
int DCF77::PreviousLeadingEdge=0;
bool DCF77::Up= false;

// DCF77 and internal timestamps
time_t DCF77::latestupdatedTime= 0;
time_t DCF77::previousUpdatedTime= 0;
time_t DCF77::processingTimestamp= 0;
time_t DCF77::previousProcessingTimestamp=0;
unsigned char DCF77::CEST=0;
DCF77::ParityFlags DCF77::flags = {0,0,0,0};
