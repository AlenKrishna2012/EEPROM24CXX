#include <cassert>
#include <cstdio>
#include "Arduino.h"
#include "Wire.h"
SerialMock Serial;
WireMock Wire;
#include "../../src/EEPROM24CXX.h"
int main(){
 Wire.reset();
 mem_init(C24C02);
 assert(EEPROM24CXX_READY());
 assert(size()==256);
 assert(writeByte(0,42));
 assert(readByte(0)==42);
 assert(!writeByte(256,1));
 assert(!EEPROM24CXX_Internal::checkAddress(255,2));
 uint8_t src[]={1,2,3,4},dst[]={0,0,0,0};
 mem_seek(10);assert(w_bytes(src,4));assert(position()==14);
 mem_seek(10);assert(r_bytes(dst,4));assert(position()==14);
 for(int i=0;i<4;i++)assert(src[i]==dst[i]);
 assert(fill(20,8,0x5A));
 assert(readByte(23)==0x5A);
 assert(wipe(20,8));
 assert(readByte(20)==255);
 assert(overwrite(30,(uint16_t)0x1234));
 assert(verify(30,(uint16_t)0x1234));
 assert(!overwrite(255,(uint16_t)1));
 puts("EEPROM24CXX native mock tests: PASS");
}
