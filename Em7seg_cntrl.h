//- -----------------------------------------------------------------------------------------------------------------------
// Em7seg_cntrl
// 2020-02-16 jp112sdl Creative Commons - http://creativecommons.org/licenses/by-nc-sa/3.0/de/
//- -----------------------------------------------------------------------------------------------------------------------

#ifndef EM7SEG_CNTRL_H_
#define EM7SEG_CNTRL_H_

#define MCP23017_IODIRA 0x00
#define MCP23017_IODIRB 0x01
#define MCP23017_GPIOA  0x12
#define MCP23017_GPIOB  0x13
#define MCP23017_OLATA  0x14
#define MCP23017_OLATB  0x15

//                 GFEDCBA
#define NUM_0   0b00111111  //        SegA:0
#define NUM_1   0b00000110  //       --------
#define NUM_2   0b01011011  //      |        |
#define NUM_3   0b01001111  //SegF:5|        |SegB:1
#define NUM_4   0b01100110  //      | SegG:6 |
#define NUM_5   0b01101101  //       --------
#define NUM_6   0b01111101  //      |        |
#define NUM_7   0b00000111  //SegE:4|        |SegC:2
#define NUM_8   0b01111111  //      |        |
#define NUM_9   0b01101111  //       --------
#define NUM_OFF 0b00000000  //        SegD:3
#define NUM_MIN 0b01000000  //
#define SEG_INV 0b00000000  // <- change polarity for single segment

#define NUM_ARRAY_LEN   12
uint8_t Numbers[NUM_ARRAY_LEN] = {NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9, NUM_OFF, NUM_MIN};

#include <Wire.h>

class WireType {
private:
  uint8_t MCP23017_ADDRESS = 0x20;

  uint8_t regForPin(uint8_t pin, uint8_t portAaddr, uint8_t portBaddr){
    return (pin<8) ? portAaddr : portBaddr;
  }

  uint8_t readRegister(uint8_t addr){
    Wire.beginTransmission(MCP23017_ADDRESS);
    Wire.write(addr);
    Wire.endTransmission();
    Wire.requestFrom((uint8_t)MCP23017_ADDRESS, (uint8_t)1);
    return Wire.read();
  }

  void updateRegisterBit(uint8_t pin, uint8_t pValue, uint8_t portAaddr, uint8_t portBaddr) {
    uint8_t regAddr=regForPin(pin,portAaddr,portBaddr);
    uint8_t bit=pin%8;
    uint8_t regValue = readRegister(regAddr);
    bitWrite(regValue,bit,pValue);
    writeRegister(regAddr,regValue);
  }

  void writeRegister(uint8_t regAddr, uint8_t regValue){
    Wire.beginTransmission(MCP23017_ADDRESS);
    Wire.write(regAddr);
    Wire.write(regValue);
    Wire.endTransmission();
  }

  void pinMode(uint8_t p, uint8_t d) {
    updateRegisterBit(p,(d==INPUT),MCP23017_IODIRA,MCP23017_IODIRB);
  }


  void digitalWriteMCP(uint8_t pin, uint8_t d) {
    uint8_t bit=pin%8;
    uint8_t regAddr=regForPin(pin,MCP23017_OLATA,MCP23017_OLATB);
    uint8_t gpio = readRegister(regAddr);
    bitWrite(gpio,bit,d);
    regAddr=regForPin(pin,MCP23017_GPIOA,MCP23017_GPIOB);
    writeRegister(regAddr,gpio);
  }

public:
  void init(uint8_t addr) {
#ifndef DRY_RUN
    MCP23017_ADDRESS = addr;
    Wire.begin();
    writeRegister(MCP23017_IODIRA,0xff);
    writeRegister(MCP23017_IODIRB,0xff);
    for (uint8_t i = 0; i < 15; i++){
      pinMode(i, OUTPUT);
      digitalWriteMCP(i, HIGH);
    }
#endif
  }

  void setPin(uint8_t pin, uint8_t d) {
#ifndef DRY_RUN
    digitalWriteMCP(pin, d);
#endif
  }
};

template <class WIREType>
class SegmentModul {
protected:
  WIREType w;
private:
  byte segmentStatus;

public:
  void init(uint8_t addr) {
    w.init(addr);
    for (uint8_t i = 0; i < 7; i++) {
      setSeg(i, 0);
    }
    segmentStatus = 0b00000000;
  }

  void setIdle (uint8_t seg) {
    w.setPin( seg * 2,      HIGH);
    w.setPin((seg * 2) + 1, HIGH);
  }

  void setSeg (uint8_t seg, bool state) {
    bool inv = bitRead(SEG_INV, seg);
    if (state == 1) {
      w.setPin( seg * 2,      inv ? LOW : HIGH);
      w.setPin((seg * 2) + 1, inv ? HIGH : LOW);
      segmentStatus |= 1 << seg;
    } else {
      w.setPin( seg * 2,      inv ? HIGH : LOW);
      w.setPin((seg * 2) + 1, inv ? LOW : HIGH);
      segmentStatus &= ~(1 << seg);
    }
    delay(2);
    setIdle(seg);
#if LOGLEVEL==3
    pf(F("SegmentModul: segmentStatus: 0b%d%d%d%d%d%d%d%d\n"),bitRead(segmentStatus,7), bitRead(segmentStatus,6),bitRead(segmentStatus,5),bitRead(segmentStatus,4),bitRead(segmentStatus,3),bitRead(segmentStatus,2),bitRead(segmentStatus,1),bitRead(segmentStatus,0) );
#endif
  }

  void showNumber(uint8_t num_idx) {
#if LOGLEVEL > 0
      pf(F("SegmentModul: showNumber(num_idx = %d)\n"),num_idx);
#endif
    for (uint8_t i = 0; i < 8; i++){
      uint8_t b  = bitRead(Numbers[num_idx] & 0xff,  i);
      uint8_t st = bitRead(segmentStatus, i);
#if LOGLEVEL > 2
      pf(F(" -  b[%d] = %d | st[%d] = %d\n"), i, b, i, st);
#endif
      if (st != b) {
#if LOGLEVEL > 1
        pf(F("  - setSeg(%d, %d)\n"), i, b);
#endif
        setSeg(i, b);
      }
    }
  }
};

template <uint8_t ModuleCount = 1>
class DisplayWithSegmentModules {
protected:
  SegmentModul<WireType> segmentModul[ModuleCount];
private:
  uint32_t pows [8] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000 } ;
public:
  void init() {
    for (uint8_t i = 0; i < ModuleCount; i++) {
#if LOGLEVEL==3
      pf(F("DisplayWithSegmentModules: init() #%d\n"), i);
#endif
      segmentModul[i].init(0x20 + i);
    }
  }

  void displaySingleDigit(uint8_t module, uint8_t num_idx) {
    pf(F("DisplayWithSegmentModules: displaySingleDigit(uint8_t module, uint8_t num) with %d, %d\n"), module, num_idx);
    if (module > 0 && module <= ModuleCount) {
      if (num_idx > 0 && num_idx < NUM_ARRAY_LEN) {
        segmentModul[module - 1].showNumber(num_idx);
      } else {
        pf(F("displaySingleDigit: given number index (%i) is out of range (0 ... %d)\n"), num_idx, NUM_ARRAY_LEN);
      }
    } else {
      pf(F("selected module (%i) is out of range. must be 1 ... %d\n"),module, ModuleCount);
    }
  }

  void displayNumber(long num) {
    long range = pow(10, ModuleCount);
    if (num > (-1 * range) && num < range) {
      uint8_t digits[ModuleCount];
      memset(digits,Numbers[10],ModuleCount);

      bool negative = num < 0;

      uint8_t len = 0;
      if (ModuleCount > 0 && abs(num) >= 0)        len++;
      if (ModuleCount > 1 && abs(num) >= 10)       len++;
      if (ModuleCount > 2 && abs(num) >= 100)      len++;
      if (ModuleCount > 3 && abs(num) >= 1000)     len++;
      if (ModuleCount > 4 && abs(num) >= 10000)    len++;
      if (ModuleCount > 5 && abs(num) >= 100000)   len++;
      if (ModuleCount > 6 && abs(num) >= 1000000)  len++;
      if (ModuleCount > 7 && abs(num) >= 10000000) len++;

      for (uint8_t i = 0; i < len; i++) {
        digits[i] = abs(num) / pows[i] % 10;
      }
      if (negative) digits[len] = 11;

      for (uint8_t i = 0; i < ModuleCount; i++) {
        segmentModul[i].showNumber(digits[i]);
      }
    } else {
      Serial.println(F("Number has too many digits"));
    }
  }

  void displayAll(uint8_t n) {
#if LOGLEVEL > 2
      pf(F("DisplayWithSegmentModules: displayAll() with %d\n"), n);
#endif
    for (uint8_t i = 0; i < ModuleCount; i++) {
      segmentModul[i].showNumber(n);
    }
  }

  void clear() {
#if LOGLEVEL > 2
      Serial.println(F("DisplayWithSegmentModules: clear()"));
#endif
    displayAll(10);
  }

};

#endif /* EM7SEG_CNTRL_H_ */
