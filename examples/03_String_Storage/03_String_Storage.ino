#include <EEPROM24CXX.h>

void setup()
{
    Serial.begin(115200);

    mem_init(C24C02);


    mem_seek(0);

    w_str("Hello EEPROM");


    mem_seek(0);


    Serial.println(
        r_str()
    );
}


void loop(){}
