/*
  examples/05_Buffer_Read_Write/05_Buffer_Read_Write.ino
  Example: Buffer Read/Write
  Description: Write an array of bytes to EEPROM and read them back into a buffer.
  Author: AlenKrishna2012
  Date: 2026-08-03
  License: MIT (see repository LICENSE)
*/

#include <EEPROM24CXX.h>

// Example: Buffer Read/Write
// Shows how to write an array of bytes to EEPROM and read them back into a buffer.

uint8_t data[] =
{
    10,20,30,40,50
};


void setup()
{
    Serial.begin(115200);

    // Initialize for 24C02 device.
    mem_init(C24C02);

    // Move pointer to start before writing the buffer.
    mem_seek(0);

    // Write 5 bytes from the data array into EEPROM.
    w_bytes(data,5);

    // Rewind pointer to the start to read back.
    mem_seek(0);

    uint8_t buffer[5];

    // Read 5 bytes into buffer from EEPROM.
    r_bytes(buffer,5);

    // Print each read byte to Serial for verification.
    for(int i=0;i<5;i++)
        Serial.println(buffer[i]);
}


void loop(){}
