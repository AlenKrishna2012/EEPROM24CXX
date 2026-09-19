#include <EEPROM24CXX.h>

void setup()
{
    Serial.begin(115200);

    mem_init(C24C02);

    fill(0, 16, 0xAA);
    fill(32, 16, 0xAA);

    bool same = compare(0, 32, 16);

    Serial.print("Memory regions are ");
    Serial.println(same ? "equal" : "different");
}

void loop()
{
}
