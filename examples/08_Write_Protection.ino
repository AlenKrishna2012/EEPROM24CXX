#include <EEPROM24CXX.h>


#define WP_PIN 5


void setup()
{
    Serial.begin(115200);


    mem_init(
        C24C02,
        0x50,
        WP_PIN
    );


    lock_mem();


    Serial.println("Locked");


    unlock_mem();


    Serial.println("Unlocked");
}


void loop(){}