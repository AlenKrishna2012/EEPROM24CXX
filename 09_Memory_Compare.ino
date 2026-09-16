/*
  examples/09_Memory_Compare/09_Memory_Compare.ino
  Example: Memory Compare
  Description: Compare EEPROM contents against a buffer or pattern and report the result.
  Author: AlenKrishna2012
  Date: 2026-08-03
  License: MIT (see repository LICENSE)
*/

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
