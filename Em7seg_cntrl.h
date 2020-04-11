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

#define INDICATOR_LED_PIN 14
#define ON  1
#define OFF 0

//                          GFEDCBA
#define NUM_SEGMENTS_0   0b00111111  //        SegA:0
#define NUM_SEGMENTS_1   0b00000110  //       --------
#define NUM_SEGMENTS_2   0b01011011  //      |        |
#define NUM_SEGMENTS_3   0b01001111  //SegF:5|        |SegB:1
#define NUM_SEGMENTS_4   0b01100110  //      | SegG:6 |
#define NUM_SEGMENTS_5   0b01101101  //       --------
#define NUM_SEGMENTS_6   0b01111101  //      |        |
#define NUM_SEGMENTS_7   0b00000111  //SegE:4|        |SegC:2
#define NUM_SEGMENTS_8   0b01111111  //      |        |
#define NUM_SEGMENTS_9   0b01101111  //       --------
#define NUM_SEGMENTS_OFF 0b00000000  //        SegD:3
#define NUM_SEGMENTS_MIN 0b01000000  //

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

#define NUM_SEGMENTS_ARRAY_LEN   12
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
    NUM_SEGMENTS_MIN};

#define CHR_SEGMENTS_ARRAY_LEN 19
const uint8_t Characters[CHR_SEGMENTS_ARRAY_LEN][2] = {
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

#include <Wire.h>

class MCP23017Type {
private:
  uint8_t MCP23017_ADDRESS = 0x20;
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

  void digitalWriteMCP(uint8_t pin, uint8_t d) {
    uint8_t bit=pin%8;
    uint8_t regAddr=regForPin(pin,MCP23017_OLATA,MCP23017_OLATB);
    uint8_t gpio = readRegister(regAddr);
    bitWrite(gpio,bit,d);
    regAddr=regForPin(pin,MCP23017_GPIOA,MCP23017_GPIOB);
    writeRegister(regAddr,gpio);
  }

public:
  bool init(uint8_t addr) {
    MCP23017_ADDRESS = addr;
    if (initWire(MCP23017_ADDRESS) == true) {
      writeRegister(MCP23017_IODIRA,0xff);
      writeRegister(MCP23017_IODIRB,0xff);
      for (uint8_t i = 0; i < 15; i++){
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

template <class MCP23017Type>
class EM7Module {
protected:
  MCP23017Type w;
private:
  byte segmentStatus;

  void setSeg (uint8_t seg, bool state) {
    setIndicatorLED(OFF);
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
  bool init(uint8_t addr) {
    if (w.init(addr) == true) {
      for (uint8_t i = 0; i < 7; i++) {
        setSeg(i, 0);
      }
      segmentStatus = 0b00000000;
      return true;
    }
    return false;
  }

  void setIndicatorLED(bool state) {
    w.setPin(INDICATOR_LED_PIN, state);
  }

  void setIdle (uint8_t seg) {
    w.setPin( seg * 2,      LOW);
    w.setPin((seg * 2) + 1, LOW);
    setIndicatorLED(ON);
  }

  void showSegments(uint8_t segments) {
    if (segments != segmentStatus) {
      for (uint8_t i = 0; i < 8; i++){
        uint8_t b  = bitRead(segments & 0xff,  i);
        uint8_t st = bitRead(segmentStatus, i);
        if (st != b) {
          setSeg(i, b);
        }
      }
    }
  }
};

class EM7ModuleArray {
protected:
  EM7Module<MCP23017Type> em7Module[8];
private:
  uint32_t pows [8] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000 } ;
  uint8_t mod_cnt = 0;
public:
  uint8_t init() {
    Wire.begin();
    for (uint8_t i = 0; i < 8; i++) {
      uint8_t addr = 0x20 + i;
      Wire.beginTransmission(addr);
      if (Wire.endTransmission() == 0) {
        pf(F("Found module[%d] at address %#01x\n"), mod_cnt, addr);
        em7Module[mod_cnt++].init(addr);
      }
    }
    pf(F("Init done. Found %d modules\n"), mod_cnt);
    return mod_cnt;
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

  void displayNumber(long num) {
    long range = pow(10, mod_cnt);
    if (num > (-1 * range) && num < range) {
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
      if (negative) digits[len] = NUM_MINUS;

      for (uint8_t i = 0; i < mod_cnt; i++) {
        em7Module[i].showSegments(Numbers[digits[i]]);
      }
    } else {
      Serial.println(F("Number has too many digits"));
    }
  }

  void displayAll(uint8_t number) {
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
      pf(F("displayWord: text length exceeds module count"));
    } else {
      for (uint8_t i = 0; i < strlen(txt); i++) {
        displaySingleChar(strlen(txt)-i,txt[i]);
      }
    }
  }

  void clear() {
#if LOGLEVEL > 2
      Serial.println(F("DisplayWithSegmentModules: clear()"));
#endif
      displayNumberAll(NUM_OFF);
  }
};

#endif /* EM7SEG_CNTRL_H_ */
