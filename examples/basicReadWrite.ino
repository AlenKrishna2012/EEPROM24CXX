#include <EEPROM24CXX.h>

void setup() {
  mem_init(C24C02);

  w_int(123456);
  w_str("Hello EEPROM");

  mem_seek(0);

  Serial.println(r_int());
  Serial.println(r_str());
}

void loop() {
}