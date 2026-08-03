#ifndef EEPROM24CXX_H
#define EEPROM24CXX_H

#include <Arduino.h>
#include <Wire.h>

// Global configurations and operational tracking variables
inline uint8_t _ee_addr = 0x50;
inline uint16_t _p = 0;
inline uint16_t _ee_size = 256;
inline uint16_t _page_size = 8;
inline bool _addr16 = false;
inline uint8_t _wp = 255;
inline bool _blockAddress = false;


enum EEPROMType {
    C24C01,
    C24C02,
    C24C04,
    C24C08,
    C24C16,
    C24C32,
    C24C64,
    C24C128,
    C24C256,
    C24C512
};

// ========================================================
// LOW-LEVEL COMMUNICATION ENGINE
// ========================================================

inline void _writeByte(uint16_t reg, uint8_t val) {

  uint8_t dev = _ee_addr;
  uint8_t addr = reg & 0xFF;

  if (_addr16) {
    Wire.beginTransmission(dev);
    Wire.write((reg >> 8) & 0xFF);
    Wire.write(addr);
  } else {
if (_blockAddress) {
    dev += ((reg >> 8) & 0x07);
}

    Wire.beginTransmission(dev);
    Wire.write(addr);
  }

  Wire.write(val);
  Wire.endTransmission();
  delay(5);
}

inline uint8_t _readByte(uint16_t reg) {

  uint8_t dev = _ee_addr;
  uint8_t addr = reg & 0xFF;

  if (_addr16) {
    Wire.beginTransmission(dev);
    Wire.write((reg >> 8) & 0xFF);
    Wire.write(addr);
  } else {
if (_blockAddress) {
    dev += ((reg >> 8) & 0x07);
}

    Wire.beginTransmission(dev);
    Wire.write(addr);
  }

  Wire.endTransmission();

  Wire.requestFrom(dev, (uint8_t)1);

  if (Wire.available())
    return Wire.read();

  return 0xFF;
}

// ========================================================
// AUTOMATIC MEMORY-MAPPED SEQUENTIAL READ / WRITE
// ========================================================

// 1. Auto Write 4-Byte Integer (Option B - Up to 2,147,483,647)
inline void w_int(long val) {
  if (_p + 3 >= _ee_size) return;
  _writeByte(_p++, (val >> 24) & 0xFF); 
  _writeByte(_p++, (val >> 16) & 0xFF); 
  _writeByte(_p++, (val >> 8) & 0xFF);  
  _writeByte(_p++, val & 0xFF);         
}

// 2. Auto Read 4-Byte Integer (Option B)
inline long r_int() {
  if (_p + 3 >= _ee_size)
    return 0;
  long b3 = _readByte(_p++);
  long b2 = _readByte(_p++);
  long b1 = _readByte(_p++);
  long b0 = _readByte(_p++);
  return (b3 << 24) | (b2 << 16) | (b1 << 8) | b0;
}

// 3. Auto Write String (Characters + hidden '\0' terminator)
inline void w_str(const String &str) {
  if (_p >= _ee_size) return;
  for (uint16_t i = 0; i < str.length(); i++) {
    if (_p >= _ee_size) break;
    _writeByte(_p++, str[i]);
}

if (_p < _ee_size)
    _writeByte(_p++, '\0');
}

// 4. Auto Read String (Reads until structural '\0' terminator bounds)
inline String r_str() {
  String str = "";
  while (_p < _ee_size) {
    char c = (char)_readByte(_p++);
    if (c == '\0')
        break;
    str += c;
}
  return str;
}

// ========================================================
// OVERLOADED EXPLICIT OVERWRITE ACTIONS (BYPASSES CURSOR)
// ========================================================

// 5. Overwrite specific registry starting address with an Integer (4 bytes)
inline void overwrite(uint16_t reg_val, long data) {
	if (reg_val + 3 >= _ee_size) return;
  _writeByte(reg_val,     (data >> 24) & 0xFF);
  _writeByte(reg_val + 1, (data >> 16) & 0xFF);
  _writeByte(reg_val + 2, (data >> 8) & 0xFF);
  _writeByte(reg_val + 3, data & 0xFF);
}

// 6. Overwrite specific registry starting address with a String
inline void overwrite(uint16_t reg_val, const String &data) {

  for (uint16_t i = 0; i < data.length(); i++) {
    if (reg_val + i >= _ee_size)
      break;

    _writeByte(reg_val + i, data[i]);
  }

  if (reg_val + data.length() < _ee_size)
    _writeByte(reg_val + data.length(), '\0');
}

// ========================================================
// RE-SEEK OR TRACK TRACKING POSITION
// ========================================================

inline void mem_seek(uint16_t addr){
    if(addr<_ee_size)
        _p=addr;
}
inline uint16_t mem_tell(){
    return _p;
}

// ========================================================
// HARDWARE LOCKING UTILITIES
// ========================================================

inline void lock_mem()   { if (_wp != 255) digitalWrite(_wp, HIGH); } 
inline void unlock_mem() { if (_wp != 255) digitalWrite(_wp, LOW);  } 

// ========================================================
// ADMINISTRATIVE DIAGNOSTICS & SYSTEM INITIALIZATION
// ========================================================

// 7. Configurable Initialization
inline void mem_init(
    EEPROMType type,
    uint8_t i2cAddress = 0x50,
    uint8_t wpPin = 255,
    uint8_t ledPin = 13,
    bool useLed = false
) {
  Serial.begin(115200);
  Wire.begin();
  _p = 0;
  _wp = wpPin;
  _ee_addr = i2cAddress; 
  
  if (_wp != 255) {
    pinMode(_wp, OUTPUT);
    unlock_mem(); // Pulls the designated WP pin down to GND automatically
  }
  if (useLed) pinMode(ledPin, OUTPUT);
  
  Wire.beginTransmission(_ee_addr);
  if (Wire.endTransmission() == 0) {
    Serial.println(F("Connected"));
    if (useLed) digitalWrite(ledPin, HIGH);
  } else {
    Serial.println(F("Error"));
    if (useLed) { 
      for (int i = 0; i < 10; i++) { 
        digitalWrite(ledPin, !digitalRead(ledPin)); 
        delay(100); 
      } 
    }
  }
switch(type){

case C24C01:
    _ee_size=128;
    _page_size=8;
    _addr16=false;
    _blockAddress=false;
    break;

case C24C02:
    _ee_size=256;
    _page_size=8;
    _addr16=false;
    _blockAddress=false;
    break;

case C24C04:
    _ee_size=512;
    _page_size=16;
    _addr16=false;
    _blockAddress=true;
    break;

case C24C08:
    _ee_size=1024;
    _page_size=16;
    _addr16=false;
    _blockAddress=true;
    break;

case C24C16:
    _ee_size=2048;
    _page_size=16;
    _addr16=false;
    _blockAddress=true;
    break;

case C24C32:
    _ee_size=4096;
    _page_size=32;
    _addr16=true;
    _blockAddress=false;
    break;

case C24C64:
    _ee_size=8192;
    _page_size=32;
    _addr16=true;
    _blockAddress=false;
    break;

case C24C128:
    _ee_size=16384;
    _page_size=64;
    _addr16=true;
    _blockAddress=false;
    break;

case C24C256:
    _ee_size=32768;
    _page_size=64;
    _addr16=true;
    _blockAddress=false;
    break;

case C24C512:
    _ee_size=65536;
    _page_size=128;
    _addr16=true;
    _blockAddress=false;
    break;

}
}

// 8. Dump all 256 bytes cleanly to the Serial Monitor matrix
inline void read_all() {
  Serial.print(F("\n--- EEPROM MEMORY MAP (0-"));
Serial.print(_ee_size - 1);
Serial.println(F(") ---"));
  for(uint16_t i=0;i<_ee_size;i++) {
    if (i % 16 == 0) { 
      if (i > 0) Serial.println(); 
      if (i < 0x10) Serial.print("000");
      else if (i < 0x100) Serial.print("00");
      else if (i < 0x1000) Serial.print('0');
      Serial.print(i, HEX); 
      Serial.print(F(": ")); 
    }
    uint8_t val = _readByte(i); 
    if (val < 16) Serial.print('0'); 
    Serial.print(val, HEX); 
    if (i % 16 != 15) Serial.print(' ');
  }
  Serial.println(F("\n---------------------------------"));
}

// 9. Wipe all 256 bytes of memory back to factory default (0xFF)
inline void wipe_all() {
	unlock_mem();
  Serial.print(F("Wiping memory..."));
  for(uint16_t i=0;i<_ee_size;i++) {
    _writeByte(i, 0xFF);
  }
  _p = 0; 
  lock_mem();
  Serial.println(F(" Done!"));
}

#endif

