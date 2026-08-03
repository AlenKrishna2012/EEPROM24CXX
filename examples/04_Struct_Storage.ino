#include <EEPROM24CXX.h>


struct Settings
{
    int speed;
    float voltage;
};


void setup()
{
    Serial.begin(115200);

    mem_init(C24C02);


    Settings data;

    data.speed=150;
    data.voltage=3.3;


    overwrite(20,data);


    Settings result;


    read(20,result);


    Serial.println(result.speed);
    Serial.println(result.voltage);
}


void loop(){}