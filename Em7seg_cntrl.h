//- -----------------------------------------------------------------------------------------------------------------------
// Em7seg_cntrl
// 2020-02-16 jp112sdl Creative Commons - http://creativecommons.org/licenses/by-nc-sa/3.0/de/
//- -----------------------------------------------------------------------------------------------------------------------

#ifndef EM7SEG_CNTRL_H_
#define EM7SEG_CNTRL_H_

//um -1 in einem einzelnen Segment anzuzeigen (z.B. bei Thermometern)
//#define MINUS10_CONDENSED

#include "printf_helper.h"

#define MCP23017_IODIRA 0x00
#define MCP23017_IODIRB 0x01
#define MCP23017_GPIOA  0x12
#define MCP23017_GPIOB  0x13
#define MCP23017_OLATA  0x14
#define MCP23017_OLATB  0x15

#define ON  1
#define OFF 0

//                           GFEDCBA
#define NUM_SEGMENTS_0    0b00111111  //        SegA:0
#define NUM_SEGMENTS_1    0b00000110  //       --------
#define NUM_SEGMENTS_2    0b01011011  //      |        |
#define NUM_SEGMENTS_3    0b01001111  //SegF:5|        |SegB:1
#define NUM_SEGMENTS_4    0b01100110  //      | SegG:6 |
#define NUM_SEGMENTS_5    0b01101101  //       --------
#define NUM_SEGMENTS_6    0b01111101  //      |        |
#define NUM_SEGMENTS_7    0b00000111  //SegE:4|        |SegC:2
#define NUM_SEGMENTS_8    0b01111111  //      |        |
#define NUM_SEGMENTS_9    0b01101111  //       --------
#define NUM_SEGMENTS_OFF  0b00000000  //        SegD:3
#define NUM_SEGMENTS_MIN  0b01000000  //
#define NUM_SEGMENTS_MIN1 0b01000110  //

#define CHR_SEGMENTS_MIN { 45,  NUM_SEGMENTS_MIN }
#define CHR_SEGMENTS_0   { 48,  NUM_SEGMENTS_0 }
#define CHR_SEGMENTS_1   { 49,  NUM_SEGMENTS_1 }
#define CHR_SEGMENTS_2   { 50,  NUM_SEGMENTS_2 }
#define CHR_SEGMENTS_3   { 51,  NUM_SEGMENTS_3 }
#define CHR_SEGMENTS_4   { 52,  NUM_SEGMENTS_4 }
#define CHR_SEGMENTS_5   { 53,  NUM_SEGMENTS_5 }
#define CHR_SEGMENTS_6   { 54,  NUM_SEGMENTS_6 }
#define CHR_SEGMENTS_7   { 55,  NUM_SEGMENTS_7 }
#define CHR_SEGMENTS_8   { 56,  NUM_SEGMENTS_8 }
#define CHR_SEGMENTS_9   { 57,  NUM_SEGMENTS_9 }
#define CHR_SEGMENTS_A   { 65,  0b01110111 }
#define CHR_SEGMENTS_C   { 67,  0b00111001 }
#define CHR_SEGMENTS_E   { 69,  0b01111001 }
#define CHR_SEGMENTS_F   { 70,  0b01110001 }
#define CHR_SEGMENTS_H   { 72,  0b01110110 }
#define CHR_SEGMENTS_I   { 73,  NUM_SEGMENTS_1 }
#define CHR_SEGMENTS_L   { 76,  0b00111000 }
#define CHR_SEGMENTS_O   { 79,  NUM_SEGMENTS_0 }
#define CHR_SEGMENTS_P   { 80,  0b01110011 }
#define CHR_SEGMENTS_S   { 83,  NUM_SEGMENTS_5 }
#define CHR_SEGMENTS_U   { 85,  0b00111110 }
#define CHR_SEGMENTS_b   { 98,  0b01111100 }
#define CHR_SEGMENTS_c   { 99,  0b01011000 }
#define CHR_SEGMENTS_d   { 100, 0b01011110 }
#define CHR_SEGMENTS_n   { 110, 0b01010100 }
#define CHR_SEGMENTS_o   { 111, 0b01011100 }
#define CHR_SEGMENTS_r   { 114, 0b01010000 }
#define CHR_SEGMENTS_t   { 116, 0b01111000 }
#define CHR_SEGMENTS_u   { 117, 0b00011100 }


#define SEG_INV          0b11111111  // <- change polarity for single segment

#define NUM_SEGMENTS_ARRAY_LEN   13
const uint8_t Numbers[NUM_SEGMENTS_ARRAY_LEN] = {
    NUM_SEGMENTS_0,
    NUM_SEGMENTS_1,
    NUM_SEGMENTS_2,
    NUM_SEGMENTS_3,
    NUM_SEGMENTS_4,
    NUM_SEGMENTS_5,
    NUM_SEGMENTS_6,
    NUM_SEGMENTS_7,
    NUM_SEGMENTS_8,
    NUM_SEGMENTS_9,
    NUM_SEGMENTS_OFF,
    NUM_SEGMENTS_MIN,
    NUM_SEGMENTS_MIN1
    };

#define CHR_SEGMENTS_ARRAY_LEN 30
const uint8_t Characters[CHR_SEGMENTS_ARRAY_LEN][2] = {
    CHR_SEGMENTS_MIN,
    CHR_SEGMENTS_0,
    CHR_SEGMENTS_1,
    CHR_SEGMENTS_2,
    CHR_SEGMENTS_3,
    CHR_SEGMENTS_4,
    CHR_SEGMENTS_5,
    CHR_SEGMENTS_6,
    CHR_SEGMENTS_7,
    CHR_SEGMENTS_8,
    CHR_SEGMENTS_9,
    CHR_SEGMENTS_A,
    CHR_SEGMENTS_C,
    CHR_SEGMENTS_E,
    CHR_SEGMENTS_F,
    CHR_SEGMENTS_H,
    CHR_SEGMENTS_I,
    CHR_SEGMENTS_L,
    CHR_SEGMENTS_O,
    CHR_SEGMENTS_P,
    CHR_SEGMENTS_S,
    CHR_SEGMENTS_U,
    CHR_SEGMENTS_b,
    CHR_SEGMENTS_c,
    CHR_SEGMENTS_d,
    CHR_SEGMENTS_n,
    CHR_SEGMENTS_o,
    CHR_SEGMENTS_r,
    CHR_SEGMENTS_t,
    CHR_SEGMENTS_u
};

#define NUM_0      0
#define NUM_1      1
#define NUM_2      2
#define NUM_3      3
#define NUM_4      4
#define NUM_5      5
#define NUM_6      6
#define NUM_7      7
#define NUM_8      8
#define NUM_9      9
#define NUM_OFF   10
#define NUM_MINUS 11
#define NUM_MINUS1 12

#include <Wire.h>

class PCF8575Type {
private:
  uint8_t  PCF8575_ADDRESS = 0x20;
  bool     INVERT          = false;
  uint16_t dataValue       = 0x0000;
  bool     available       = false;

  bool initWire(uint8_t addr) {
    Wire.beginTransmission(addr);
    return (Wire.endTransmission() == 0);
  }

  void digitalWritePCF(uint8_t pin, bool d) {
    bool val = (INVERT == true) ? !d : d;
    if (val == HIGH) {
      dataValue &= ~(1 << pin);
    } else {
      dataValue |= (1 << pin);
    }
    Wire.beginTransmission(PCF8575_ADDRESS);
    Wire.write(dataValue >> 8);        //  high 8 bits
    Wire.write(dataValue & 0xFF);      //  low 8 bits
    Wire.endTransmission();
  }

public:
  bool init(uint8_t addr, bool inv) {
    PCF8575_ADDRESS = addr;
    INVERT = inv;

    if (initWire(PCF8575_ADDRESS) == true) {
      for (uint8_t i = 0; i < 16; i++){
        digitalWritePCF(i, HIGH);
      }
#if LOGLEVEL > 2
      pf(F("PCF8575Type: init PCF8575 with address %#01x done\n"),addr);
#endif
      available = true;
      return true;
    }
    pf(F("PCF8575Type: no PCF8575 found at address %#01x\n"),addr);
    available = false;
    return false;
  }

  void setPin(uint8_t pin, uint8_t d) {
    if (available) digitalWritePCF(pin, d);
  }
};

class MCP23017Type {
private:
  uint8_t MCP23017_ADDRESS = 0x20;
  bool    INVERT           = false;
  bool    available        = false;

  bool initWire(uint8_t addr) {
    Wire.beginTransmission(addr);
    return (Wire.endTransmission() == 0);
  }

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

  void digitalWriteMCP(uint8_t pin, bool d) {
    uint8_t bit=pin%8;
    uint8_t regAddr=regForPin(pin,MCP23017_OLATA,MCP23017_OLATB);
    uint8_t gpio = readRegister(regAddr);
    bool val = (INVERT == true) ? !d : d;
    bitWrite(gpio,bit,val);
    regAddr=regForPin(pin,MCP23017_GPIOA,MCP23017_GPIOB);
    writeRegister(regAddr,gpio);
  }

public:
  bool init(uint8_t addr, bool inv) {
    MCP23017_ADDRESS = addr;
    INVERT = inv;
    if (initWire(MCP23017_ADDRESS) == true) {
      writeRegister(MCP23017_IODIRA,0xff);
      writeRegister(MCP23017_IODIRB,0xff);
      for (uint8_t i = 0; i < 16; i++){
        pinMode(i, OUTPUT);
        digitalWriteMCP(i, LOW);
      }
#if LOGLEVEL > 2
      pf(F("MCP23017Type: init MCP23017 with address %#01x done\n"),addr);
#endif
      available = true;
      return true;
    }
    pf(F("MCP23017Type: no MCP23017 found at address %#01x\n"),addr);
    available = false;
    return false;
  }

  void setPin(uint8_t pin, uint8_t d) {
    if (available) digitalWriteMCP(pin, d);
  }
};

template <class ControllerType>
class EM7Module {
protected:
  ControllerType w;
private:
  byte segmentStatus;
  uint16_t dly = 0;

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

public:
  bool init(uint8_t addr, bool invert) {
    if (w.init(addr, invert) == true) {
      for (uint8_t i = 0; i < 7; i++) {
        setSeg(i, 0);
      }
      segmentStatus = 0b00000000;
      return true;
    }
    return false;
  }

  void setIdle (uint8_t seg) {
    w.setPin( seg * 2,      LOW);
    w.setPin((seg * 2) + 1, LOW);
  }

  void setSegToSegDelayMillis(uint16_t d) {
    dly = d;
  }

  void showSegments(uint8_t segments) {
    if (segments != segmentStatus) {
      for (uint8_t i = 0; i < 8; i++){
        uint8_t b  = bitRead(segments & 0xff, i);
        uint8_t st = bitRead(segmentStatus,   i);
        if (st != b) {
          setSeg(i, b);
          delay(dly);
        }
      }
    }
  }
};

template <class ControllerType, uint8_t moduleCount>
class EM7ModuleArray {
protected:
  EM7Module<ControllerType> em7Module[8];
private:
  uint32_t pows [8] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000 } ;
  uint8_t mod_cnt = 0;
  uint16_t dly = 0;
public:
  uint8_t initAddressed(const uint8_t * addrArray, const uint8_t ENABLE_PIN=0, const bool INVERT = false) {
    if (ENABLE_PIN != 0) {
      pinMode(ENABLE_PIN, OUTPUT);
      digitalWrite(ENABLE_PIN, HIGH);
      delay(100);
      digitalWrite(ENABLE_PIN, LOW);
      delay(100);
    }

    Wire.begin();
    for (uint8_t i = 0; i < moduleCount; i++) {
      uint8_t addr = addrArray[i];
      Wire.beginTransmission(addr);
      if (Wire.endTransmission() == 0) {
        pf(F("Found module[%d] at address %#01x\n"), mod_cnt, addr);
        em7Module[mod_cnt++].init(addr,INVERT);
      }
    }
    pf(F("Init done. Found %d modules\n"), mod_cnt);
    return mod_cnt;
  }

  uint8_t init(const uint8_t ENABLE_PIN=0, const bool INVERT = false) {
    const uint8_t addresses[8] = {0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27};
    return initAddressed(addresses, ENABLE_PIN, INVERT);
  }

  void setSegToSegDelayMillis(uint16_t d) {
    for (uint8_t i = 0; i < mod_cnt; i++) {
      dly = d;
      em7Module[i].setSegToSegDelayMillis(dly);
    }
  }

  void showSegments(uint8_t module, uint8_t segments) {
    em7Module[module-1].showSegments(segments);
  }

  void displaySingleDigit(uint8_t module, uint8_t num_idx) {
#if LOGLEVEL > 0
    pf(F("DisplayWithSegmentModules: displaySingleDigit(uint8_t module, uint8_t num) with %d, %d\n"), module, num_idx);
#endif
    if (module > 0 && module <= mod_cnt) {
      if (num_idx < NUM_SEGMENTS_ARRAY_LEN) {
        em7Module[module - 1].showSegments(Numbers[num_idx]);
      } else {
        pf(F("displaySingleDigit: given number index (%i) is out of range (0 ... %d)\n"), num_idx, NUM_SEGMENTS_ARRAY_LEN);
      }
    } else {
      pf(F("selected module (%i) is out of range. must be 1 ... %d\n"),module, mod_cnt);
    }
  }

  void displayNumber(long num, bool leadingZero, bool alignRight=true) {
    long range = pow(10, mod_cnt);
    if (abs(num) > range) { pf(F("Number has too many digits\n")); return; }
    uint8_t digits[mod_cnt];
    memset(digits,Numbers[NUM_OFF],mod_cnt);

    bool negative = num < 0;

    uint8_t len = 0;
    if (mod_cnt > 0 && abs(num) >= 0)        len++;
    if (mod_cnt > 1 && abs(num) >= 10)       len++;
    if (mod_cnt > 2 && abs(num) >= 100)      len++;
    if (mod_cnt > 3 && abs(num) >= 1000)     len++;
    if (mod_cnt > 4 && abs(num) >= 10000)    len++;
    if (mod_cnt > 5 && abs(num) >= 100000)   len++;
    if (mod_cnt > 6 && abs(num) >= 1000000)  len++;
    if (mod_cnt > 7 && abs(num) >= 10000000) len++;

    for (uint8_t i = 0; i < len; i++) {
      digits[i] = abs(num) / pows[i] % 10;
    }

#ifndef MINUS10_CONDENSED
    if (negative) digits[len] = NUM_MINUS;
#else
    if (negative) {
      if ( num <= - 100 && num > -200) {
        digits[mod_cnt-1] = NUM_MINUS1;
      } else {
        digits[mod_cnt-1] = NUM_MINUS; // minus sign most left
      }
    }
#endif

    if (alignRight) {
      for (uint8_t i = 0; i < mod_cnt; i++) {
        if (leadingZero==false && i >= len)
          em7Module[i].showSegments(Numbers[NUM_OFF]);
        else
          em7Module[i].showSegments(Numbers[digits[i]]);
      }
    } else {
      Serial.println("align left");
      for (uint8_t i = 0; i < mod_cnt; i++) {
        em7Module[mod_cnt - i].showSegments(Numbers[ (i > len) ? NUM_OFF : digits[len - i]]);
      }
    }
  }

  void displayNumberAll(uint8_t number) {
#if LOGLEVEL > 2
      pf(F("DisplayWithSegmentModules: displayAll() with %d\n"), number);
#endif
    for (uint8_t i = 0; i < mod_cnt; i++) {
      em7Module[i].showSegments(Numbers[number]);
    }
  }

  void displaySingleChar(uint8_t module, char chr) {
#if LOGLEVEL > 0
    pf(F("DisplayWithSegmentModules: displaySingleChar(uint8_t module, char chr) with %d, %d\n"), module, chr);
#endif
    if (module > 0 && module <= mod_cnt) {
      uint8_t chr_idx = 255;
      for (uint8_t i = 0; i < CHR_SEGMENTS_ARRAY_LEN; i++) {
        if (chr == Characters[i][0]) {
          chr_idx = i;
          break;
        }
      }
      if (chr_idx < 255) {
        em7Module[module - 1].showSegments(Characters[chr_idx][1]);
      } else {
        pf(F("displaySingleChar: character not found \n"));
      }
    } else {
      pf(F("selected module (%i) is out of range. must be 1 ... %d\n"),module, mod_cnt);
    }
  }

  void displayWord(const char * txt) {

    if (strlen(txt) > mod_cnt) {
      pf(F("displayWord: text length exceeds module count\n"));
    } else {
      for (uint8_t i = 0; i < strlen(txt); i++) {
        displaySingleChar(strlen(txt)-i,txt[i]);
      }
    }
  }

  void clear() {
    uint16_t _dly = dly;
    setSegToSegDelayMillis(0);
#if LOGLEVEL > 2
      Serial.println(F("DisplayWithSegmentModules: clear()"));
#endif
    displayNumberAll(NUM_OFF);

    setSegToSegDelayMillis(_dly);
  }
};

#endif /* EM7SEG_CNTRL_H_ */
