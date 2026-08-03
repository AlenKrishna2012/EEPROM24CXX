/*
  examples/06_EEPROM_Dump/06_EEPROM_Dump.ino
  Example: EEPROM Dump
  Description: Initialize the EEPROM and dump its contents to Serial using read_all().
  Author: AlenKrishna2012
  Date: 2026-08-03
  License: MIT (see repository LICENSE)
*/

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
