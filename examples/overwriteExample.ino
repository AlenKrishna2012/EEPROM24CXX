#include <EEPROM24CXX.h>

void setup() {
  mem_init(C24C02);

  overwrite(0, 98765);
  overwrite(10, "Arduino");

  mem_seek(0);
  Serial.println(r_int());

  mem_seek(10);
  Serial.println(r_str());
}

void loop() {
}