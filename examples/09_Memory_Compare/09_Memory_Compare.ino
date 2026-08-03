#include <EEPROM24CXX.h>

// Example: Memory Compare
// Demonstrates comparing EEPROM contents against a buffer or pattern.

void setup()
{
    Serial.begin(115200);

    // Initialize for 24C02 device.
    mem_init(C24C02);

    // Compare memory starting at address 0 and print result (function specifics in library).
    mem_compare(0);
}


void loop(){}
