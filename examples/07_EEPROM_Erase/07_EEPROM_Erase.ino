/*
  examples/07_EEPROM_Erase/07_EEPROM_Erase.ino
  Example: EEPROM Erase
  Description: Initialize the EEPROM and erase its contents using erase_all().
  Author: AlenKrishna2012
  Date: 2026-08-03
  License: MIT (see repository LICENSE)
*/

#include <EEPROM24CXX.h>

// Example: EEPROM Erase
// Demonstrates erasing (likely setting to 0xFF or 0x00 depending on implementation) the EEPROM.

void setup()
{
    Serial.begin(115200);

    // Initialize for 24C02 device.
    mem_init(C24C02);

    // Erase the EEPROM memory using the provided helper.
    wipe_all();
}


void loop(){}
