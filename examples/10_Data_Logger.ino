#include <EEPROM24CXX.h>


struct LogData
{
    uint32_t time;
    int sensor;
};


void setup()
{
    Serial.begin(115200);

    mem_init(C24C64);


    LogData log;


    log.time=millis();
    log.sensor=123;


    overwrite(
        0,
        log
    );


    LogData readLog;


    read(
        0,
        readLog
    );


    Serial.println(readLog.time);
    Serial.println(readLog.sensor);
}


void loop(){}