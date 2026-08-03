/*
  examples/02_Update_Byte/02_Update_Byte.ino
  Example: Update Byte
  Description: Initialize the EEPROM, update a byte at a specific address (only writes if different), then read and print it.
  Author: AlenKrishna2012
  Date: 2026-08-03
  License: MIT (see repository LICENSE)
*/

#include <EEPROM24CXX.h>

// Example: Update Byte
// Demonstrates initializing the EEPROM and using updateByte to change
// the value at a specific address (10), then reading and printing it.

void setup()
{
    Serial.begin(115200);

    // Initialize for 24C02 device. Change as needed for other chips.
    mem_init(C24C02);

    // Update EEPROM address 10 with value 55. updateByte only writes if value differs.
    updateByte(10,55);

    // Read back and print the value from address 10.
    Serial.println(
        readByte(10)
    );
}


void loop(){}
