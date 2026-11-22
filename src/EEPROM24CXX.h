#ifndef EEPROM24CXX_H
#define EEPROM24CXX_H
#include <Arduino.h>
#include <Wire.h>
namespace EEPROM24CXX_Internal {bool checkAddress(uint32_t,uint32_t=1);extern bool initialized;}
enum EEPROMType { C24C01,C24C02,C24C04,C24C08,C24C16,C24C32,C24C64,C24C128,C24C256,C24C512,C24CM01,C24CM02,C24CM04,C24CM08 };
void mem_init(EEPROMType,uint8_t=0x50,uint8_t=255,uint8_t=13,bool=false);
bool writeByte(uint32_t,uint8_t); uint8_t readByte(uint32_t); bool updateByte(uint32_t,uint8_t);
void lock_mem(); void unlock_mem(); void mem_seek(uint32_t); void rewind(); void skip(uint32_t); void mem_back(uint32_t); void mem_end();
uint32_t position(); uint32_t mem_remaining(); bool available(uint32_t=1); uint8_t peek();
uint32_t size(); uint16_t pageSize(); bool is16Bit(); bool usesBlockAddress();
bool w_str(const String&); String r_str(); bool w_bytes(const uint8_t*,uint32_t); bool r_bytes(uint8_t*,uint32_t);
template<typename T> bool write(const T&v){return w_bytes((const uint8_t*)&v,sizeof(T));}
template<typename T> bool read(T&v){return r_bytes((uint8_t*)&v,sizeof(T));}
template<typename T> bool update(const T&v){if(!available(sizeof(T)))return false;const uint8_t*p=(const uint8_t*)&v;uint32_t a=position();for(size_t i=0;i<sizeof(T);i++)if(readByte(a+i)!=p[i]&&!writeByte(a+i,p[i]))return false;mem_seek(a+sizeof(T));return true;}
template<typename T> bool overwrite(uint32_t a,const T&v){if(!EEPROM24CXX_Internal::checkAddress(a,sizeof(T)))return false;const uint8_t*p=(const uint8_t*)&v;for(size_t i=0;i<sizeof(T);i++)if(!writeByte(a+i,p[i]))return false;return true;}
bool overwrite(uint32_t,const String&);
template<typename T> bool read(uint32_t a,T&v){if(!EEPROM24CXX_Internal::checkAddress(a,sizeof(T)))return false;uint8_t*p=(uint8_t*)&v;for(size_t i=0;i<sizeof(T);i++)p[i]=readByte(a+i);return true;}
template<typename T> bool verify(uint32_t a,const T&v){if(!EEPROM24CXX_Internal::checkAddress(a,sizeof(T)))return false;const uint8_t*p=(const uint8_t*)&v;for(size_t i=0;i<sizeof(T);i++)if(readByte(a+i)!=p[i])return false;return true;}
bool wipe(uint32_t,uint32_t); bool fill(uint32_t,uint32_t,uint8_t); bool compare(uint32_t,uint32_t,uint32_t); bool wipe_all(); void read_all();
namespace EEPROM24CXX_Internal {extern uint8_t deviceAddress,writeProtectPin;extern uint32_t memorySize;extern uint16_t pageSize;extern bool address16Bit,blockAddressing,cm01;extern uint32_t cursor;uint8_t getDeviceAddress(uint32_t);bool waitReady(uint8_t,uint32_t=50);bool writeByteRaw(uint32_t,uint8_t);uint8_t readByteRaw(uint32_t);bool writePage(uint32_t,const uint8_t*,uint16_t);}
#define EEPROM24CXX_READY() (EEPROM24CXX_Internal::initialized)
#endif