#include <EEPROM24CXX.h>

void setup() {
  mem_init(C24C256, 0x53);

  w_str("Custom Address");

  mem_seek(0);

  Serial.println(r_str());
}

void loop() {
}