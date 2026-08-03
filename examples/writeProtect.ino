#include <EEPROM24CXX.h>

void setup() {
  mem_init(C24C02, 0x50, 7);

  unlock_mem();

  w_str("Unlocked");

  lock_mem();
}

void loop() {
}