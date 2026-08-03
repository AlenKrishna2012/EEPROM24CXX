#include <EEPROM24CXX.h>

void setup() {
  mem_init(C24C32);

  w_int(10);
  w_int(20);
  w_int(30);

  w_str("ESP32");
  w_str("Arduino");

  mem_seek(0);

  Serial.println(r_int());
  Serial.println(r_int());
  Serial.println(r_int());

  Serial.println(r_str());
  Serial.println(r_str());
}

void loop() {
}