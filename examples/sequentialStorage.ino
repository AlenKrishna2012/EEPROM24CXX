#include <EEPROM24CXX.h>

void setup() {
  mem_init(C24C256);

  w_int(111);
  w_str("First");

  w_int(222);
  w_str("Second");

  mem_seek(0);

  Serial.println(r_int());
  Serial.println(r_str());

  Serial.println(r_int());
  Serial.println(r_str());
}

void loop() {
}