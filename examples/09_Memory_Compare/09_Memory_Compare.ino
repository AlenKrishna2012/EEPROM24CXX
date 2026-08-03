#include <EEPROM24CXX.h>


void setup()
{
    Serial.begin(115200);

    mem_init(C24C02);


    writeByte(0,50);
    writeByte(100,50);


    if(compare(0,100,1))
        Serial.println("Same");
    else
        Serial.println("Different");
}


void loop(){}
