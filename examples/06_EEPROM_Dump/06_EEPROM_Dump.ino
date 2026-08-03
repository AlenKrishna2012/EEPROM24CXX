#include <EEPROM24CXX.h>

// Example: EEPROM Dump
// Initializes the EEPROM and calls read_all() to dump the memory contents to Serial.

void setup()
{
    Serial.begin(115200);

    // Initialize library for 24C02 devices.
    mem_init(C24C02);

    // Read and print the full contents of the EEPROM to Serial.
    read_all();
}


void loop(){}
