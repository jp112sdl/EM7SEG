/*
 * Em7seg_cntrl.h
 *
 *  Created on: 16 Feb 2020
 *      Author: jp112sdl

        SegA:0
       --------
      |        |
SegF:5|        |SegB:1
      | SegG:6 |
       --------
      |        |
SegE:4|        |SegC:2
      |        |
       --------
        SegD:3
 */

#ifndef EM7SEG_CNTRL_H_
#define EM7SEG_CNTRL_H_

#define MCP23017_IODIRA 0x00
#define MCP23017_IODIRB 0x01
#define MCP23017_GPIOA 0x12
#define MCP23017_GPIOB 0x13
#define MCP23017_OLATA 0x14
#define MCP23017_OLATB 0x15

#define NUM_0   0b00111111
#define NUM_1   0b00000110
#define NUM_2   0b01011011
#define NUM_3   0b01001111
#define NUM_4   0b01100110
#define NUM_5   0b01101101
#define NUM_6   0b01111101
#define NUM_7   0b00000111
#define NUM_8   0b01111111
#define NUM_9   0b01101111
#define NUM_OFF 0b00000000
#define NUM_MIN 0b01000000

uint8_t Numbers[12] = {NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9, NUM_OFF, NUM_MIN};

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
    MCP23017_ADDRESS = addr;
    Wire.begin();
    writeRegister(MCP23017_IODIRA,0xff);
    writeRegister(MCP23017_IODIRB,0xff);
    for (uint8_t i = 0; i < 15; i++){
      pinMode(i, OUTPUT);
      digitalWriteMCP(i, HIGH);
    }
  }

  void setPin(uint8_t pin, uint8_t d) {
    digitalWriteMCP(pin, d);
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
    if (state == 1) {
      w.setPin( seg * 2,      HIGH);
      w.setPin((seg * 2) + 1, LOW);
      segmentStatus |= 1 << seg;
    } else {
      w.setPin( seg * 2,      LOW);
      w.setPin((seg * 2) + 1, HIGH);
      segmentStatus &= ~(1 << seg);
    }
    delay(2);
    setIdle(seg);
  }

  void showNumber(uint8_t num) {
    for (uint8_t i = 0; i < 8; i++){
      uint8_t b  = bitRead(Numbers[num],  i);
      uint8_t st = bitRead(segmentStatus, i);
      if (st != b) {
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
      segmentModul[i].init(0x20 + i);
    }
  }

  void displayNumber(long num) {
    long range = pow(10, ModuleCount);
    if (num > (-1 * range) && num < range) {
      uint8_t digits[ModuleCount];
      memset(digits,NUM_OFF,ModuleCount);

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
      if (negative) digits[len] = NUM_MIN;

      for (uint8_t i = 0; i < ModuleCount; i++) {
        segmentModul[i].showNumber(digits[i]);
      }
    }
  }

  void displayAll(uint8_t n) {
    for (uint8_t i = 0; i < ModuleCount; i++) {
      segmentModul[i].showNumber(n);
    }
  }

  void clear() {
    displayAll(NUM_OFF);
  }

};

#endif /* EM7SEG_CNTRL_H_ */
