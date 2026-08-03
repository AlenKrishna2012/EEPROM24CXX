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
