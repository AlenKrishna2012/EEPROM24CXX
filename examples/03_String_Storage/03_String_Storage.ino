/*
  examples/03_String_Storage/03_String_Storage.ino
  Example: String Storage
  Description: Write a null-terminated string to EEPROM and read it back.
  Author: AlenKrishna2012
  Date: 2026-08-03
  License: MIT (see repository LICENSE)
*/

#include <EEPROM24CXX.h>

// Example: String Storage
// Demonstrates writing and reading a null-terminated string to/from EEPROM.

void setup()
{
    Serial.begin(115200);

    // Initialize library for 24C02 devices. Adjust if using another chip.
    mem_init(C24C02);

    // Move internal pointer to address 0 before writing.
    mem_seek(0);

    // Write a C-style string to EEPROM at the current position.
    w_str("Hello EEPROM");

    // Reset pointer back to 0 to read what was written.
    mem_seek(0);

    // Read the stored string and print it to Serial.
    Serial.println(
        r_str()
    );
}


void loop(){}
