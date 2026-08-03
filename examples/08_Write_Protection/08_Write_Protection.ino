/*
  examples/08_Write_Protection/08_Write_Protection.ino
  Example: Write Protection
  Description: Demonstrate enabling and disabling hardware write protection if supported by the device.
  Author: AlenKrishna2012
  Date: 2026-08-03
  License: MIT (see repository LICENSE)
*/

#include <EEPROM24CXX.h>

// Example: Write Protection
// Shows how to enable/disable hardware write protection if supported.

void setup()
{
    Serial.begin(115200);

    // Initialize the library for 24C02 devices.
    mem_init(C24C02);

    // Enable write protection (implementation depends on the board/hardware wiring).
    write_protect_enable();

    // Disable write protection to allow writes again.
    write_protect_disable();
}


void loop(){}
