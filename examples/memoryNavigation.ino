#include <EEPROM24CXX.h>

void setup() {
  mem_init(C24C02);

  w_int(100);
  w_int(200);
  w_int(300);

  mem_seek(4);

  Serial.println(r_int());

  Serial.print("Cursor: ");
  Serial.println(mem_tell());
}

void loop() {
}