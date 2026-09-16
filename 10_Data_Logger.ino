/*
  examples/10_Data_Logger/10_Data_Logger.ino
  Example: Data Logger
  Description: Simple example showing how to log small pieces of data into EEPROM and read them back.
  Author: AlenKrishna2012
  Date: 2026-08-03
  License: MIT (see repository LICENSE)
*/

#include <EEPROM24CXX.h>

// Example: Data Logger
// Demonstrates a simple pattern for logging data into EEPROM for later retrieval.

void setup()
{
    Serial.begin(115200);

    // Initialize the EEPROM library for a 24C02 device.
    mem_init(C24C02);

    // Example logging operation: write a sequence of values to EEPROM.
    for(int i=0;i<10;i++)
    {
        writeByte(i,(uint8_t)i);
    }

    // Read back and print logged values.
    for(int i=0;i<10;i++)
    {
        Serial.println(readByte(i));
    }
}


void loop(){}
