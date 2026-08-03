#include <EEPROM24CXX.h>

void setup()
{
    Serial.begin(115200);

    mem_init(C24C02);


    writeByte(0,123);


    uint8_t value =
    readByte(0);


    Serial.print("Value: ");
    Serial.println(value);
}


void loop(){}