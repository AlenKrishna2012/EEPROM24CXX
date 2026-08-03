#include <EEPROM24CXX.h>


void setup()
{
    Serial.begin(115200);

    mem_init(C24C02);


    read_all();
}


void loop(){}