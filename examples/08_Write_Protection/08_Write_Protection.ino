#include <EEPROM24CXX.h>

void setup()
{
    Serial.begin(115200);

    // No WP pin was supplied, so the functions safely do nothing.
    mem_init(C24C02);

    lock_mem();
    unlock_mem();
}

void loop()
{
}
