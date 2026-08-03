/*
  examples/01_Basic_Read_Write/01_Basic_Read_Write.ino
  Example: Basic Read and Write
  Description: Initialize the EEPROM, write a single byte at address 0, read it back, and print the value to Serial.
  Author: AlenKrishna2012
  Date: 2026-08-03
  License: MIT (see repository LICENSE)
*/

#include <EEPROM24CXX.h>

// Example: Basic Read and Write
// This sketch demonstrates initializing the EEPROM, writing a byte at
// address 0, then reading it back and printing the value to Serial.

void setup()
{
    Serial.begin(115200);

    // Initialize the library for a 24C02 device. Change if using a different chip.
    mem_init(C24C02);

    // Write the value 123 to EEPROM address 0.
    writeByte(0,123);

    // Read back the byte from address 0.
    uint8_t value =
    readByte(0);

    // Print the read value to the serial monitor.
    Serial.print("Value: ");
    Serial.println(value);
}


void loop(){}
