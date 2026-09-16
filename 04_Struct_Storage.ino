/*
  examples/04_Struct_Storage/04_Struct_Storage.ino
  Example: Struct Storage
  Description: Save and retrieve a C++ struct (e.g., settings/config) to/from EEPROM.
  Author: AlenKrishna2012
  Date: 2026-08-03
  License: MIT (see repository LICENSE)
*/

#include <EEPROM24CXX.h>


struct Settings
{
    int speed;
    float voltage;
};


// Example: Struct Storage
// Demonstrates writing a C++ struct to EEPROM and reading it back.
// Useful for saving configuration or settings in non-volatile memory.

void setup()
{
    Serial.begin(115200);

    // Initialize library for 24C02 devices.
    mem_init(C24C02);

    // Create and populate a Settings struct.
    Settings data;

    data.speed=150;
    data.voltage=3.3;

    // Overwrite EEPROM starting at address 20 with the struct data.
    overwrite(20,data);

    // Read the struct back from EEPROM into result.
    Settings result;

    read(20,result);

    // Print the struct fields to Serial to verify storage.
    Serial.println(result.speed);
    Serial.println(result.voltage);
}


void loop(){}
