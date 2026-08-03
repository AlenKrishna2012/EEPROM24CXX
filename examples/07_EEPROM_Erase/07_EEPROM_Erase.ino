#include <EEPROM24CXX.h>

// Example: EEPROM Erase
// Demonstrates erasing (likely setting to 0xFF or 0x00 depending on implementation) the EEPROM.

void setup()
{
    Serial.begin(115200);

    // Initialize for 24C02 device.
    mem_init(C24C02);

    // Erase the EEPROM memory using the provided helper.
    erase_all();
}


void loop(){}
