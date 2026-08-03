#include <EEPROM24CXX.h>

void setup() {
  mem_init(C24C02);

  wipe_all();

  read_all();
}

void loop() {
}