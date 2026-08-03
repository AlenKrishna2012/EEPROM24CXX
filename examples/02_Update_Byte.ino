#include <EEPROM24CXX.h>

void setup()
{
    Serial.begin(115200);

    mem_init(C24C02);


    updateByte(10,55);


    Serial.println(
        readByte(10)
    );
}


void loop(){}