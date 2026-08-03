#include <EEPROM24CXX.h>


uint8_t data[] =
{
    10,20,30,40,50
};


void setup()
{
    Serial.begin(115200);

    mem_init(C24C02);


    mem_seek(0);


    w_bytes(data,5);


    mem_seek(0);


    uint8_t buffer[5];


    r_bytes(buffer,5);


    for(int i=0;i<5;i++)
        Serial.println(buffer[i]);
}


void loop(){}
