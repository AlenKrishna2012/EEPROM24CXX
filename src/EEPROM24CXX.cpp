#include "EEPROM24CXX.h"


// ======================================================
// INTERNAL VARIABLES
// ======================================================

namespace EEPROM24CXX_Internal
{

uint8_t deviceAddress = 0x50;

uint8_t writeProtectPin = 255;


uint32_t memorySize = 256;


uint16_t pageSize = 8;


bool address16Bit = false;


bool blockAddressing = false;


uint32_t cursor = 0;


bool initialized = false;



}


// ======================================================
// LOW LEVEL DEVICE ADDRESS
// ======================================================

uint8_t EEPROM24CXX_Internal::getDeviceAddress
(
    uint32_t address
)
{

    uint8_t dev =
    deviceAddress;


    if(blockAddressing)
    {
        dev +=
        (address >> 8) & 0x07;
    }


    return dev;

}



// ======================================================
// ADDRESS CHECK
// ======================================================

bool EEPROM24CXX_Internal::checkAddress
(
    uint32_t address,
    uint32_t length
)
{

    if(address >= memorySize)
        return false;


    if((address + length) > memorySize)
        return false;


    return true;

}



// ======================================================
// WAIT EEPROM WRITE COMPLETE
// ======================================================

bool EEPROM24CXX_Internal::waitReady
(
    uint32_t timeout
)
{

    uint32_t start =
    millis();


    while(millis()-start < timeout)
    {

        Wire.beginTransmission(
            deviceAddress
        );


        if(Wire.endTransmission()==0)
            return true;


        delay(1);

    }


    return false;

}



// ======================================================
// RAW BYTE WRITE
// ======================================================

bool EEPROM24CXX_Internal::writeByteRaw
(
    uint32_t address,
    uint8_t value
)
{

    if(!checkAddress(address))
        return false;



    uint8_t dev =
    getDeviceAddress(address);



    Wire.beginTransmission(dev);



    if(address16Bit)
    {

        Wire.write(
            address >> 8
        );

        Wire.write(
            address & 0xFF
        );

    }
    else
    {

        Wire.write(
            address & 0xFF
        );

    }



    Wire.write(value);



    if(Wire.endTransmission()!=0)
        return false;



    return waitReady();

}



// ======================================================
// RAW BYTE READ
// ======================================================

uint8_t EEPROM24CXX_Internal::readByteRaw
(
    uint32_t address
)
{

    if(!checkAddress(address))
        return 0xFF;



    uint8_t dev =
    getDeviceAddress(address);



    Wire.beginTransmission(dev);



    if(address16Bit)
    {

        Wire.write(
            address >> 8
        );


        Wire.write(
            address & 0xFF
        );

    }

    else
    {

        Wire.write(
            address & 0xFF
        );

    }



    if(Wire.endTransmission()!=0)
        return 0xFF;



    Wire.requestFrom
    (
        dev,
        (uint8_t)1
    );



    if(Wire.available())
        return Wire.read();



    return 0xFF;

}
// ======================================================
// INITIALIZATION
// ======================================================

void mem_init
(
    EEPROMType type,
    uint8_t i2cAddress,
    uint8_t wpPin,
    uint8_t ledPin,
    bool useLed
)
{

    Wire.begin();


    EEPROM24CXX_Internal::deviceAddress =
    i2cAddress;


    EEPROM24CXX_Internal::writeProtectPin =
    wpPin;


    EEPROM24CXX_Internal::cursor = 0;



    if(wpPin != 255)
    {

        pinMode(
            wpPin,
            OUTPUT
        );


        unlock_mem();

    }



    if(useLed)
    {
        pinMode(
            ledPin,
            OUTPUT
        );
    }




    switch(type)
    {

        case C24C01:

            EEPROM24CXX_Internal::memorySize = 128;
            EEPROM24CXX_Internal::pageSize = 8;
            EEPROM24CXX_Internal::address16Bit = false;
            EEPROM24CXX_Internal::blockAddressing = false;

        break;



        case C24C02:

            EEPROM24CXX_Internal::memorySize = 256;
            EEPROM24CXX_Internal::pageSize = 8;
            EEPROM24CXX_Internal::address16Bit = false;
            EEPROM24CXX_Internal::blockAddressing = false;

        break;



        case C24C04:

            EEPROM24CXX_Internal::memorySize = 512;
            EEPROM24CXX_Internal::pageSize = 16;
            EEPROM24CXX_Internal::address16Bit = false;
            EEPROM24CXX_Internal::blockAddressing = true;

        break;



        case C24C08:

            EEPROM24CXX_Internal::memorySize = 1024;
            EEPROM24CXX_Internal::pageSize = 16;
            EEPROM24CXX_Internal::address16Bit = false;
            EEPROM24CXX_Internal::blockAddressing = true;

        break;



        case C24C16:

            EEPROM24CXX_Internal::memorySize = 2048;
            EEPROM24CXX_Internal::pageSize = 16;
            EEPROM24CXX_Internal::address16Bit = false;
            EEPROM24CXX_Internal::blockAddressing = true;

        break;



        case C24C32:

            EEPROM24CXX_Internal::memorySize = 4096;
            EEPROM24CXX_Internal::pageSize = 32;
            EEPROM24CXX_Internal::address16Bit = true;
            EEPROM24CXX_Internal::blockAddressing = false;

        break;



        case C24C64:

            EEPROM24CXX_Internal::memorySize = 8192;
            EEPROM24CXX_Internal::pageSize = 32;
            EEPROM24CXX_Internal::address16Bit = true;
            EEPROM24CXX_Internal::blockAddressing = false;

        break;



        case C24C128:

            EEPROM24CXX_Internal::memorySize = 16384;
            EEPROM24CXX_Internal::pageSize = 64;
            EEPROM24CXX_Internal::address16Bit = true;
            EEPROM24CXX_Internal::blockAddressing = false;

        break;



        case C24C256:

            EEPROM24CXX_Internal::memorySize = 32768;
            EEPROM24CXX_Internal::pageSize = 64;
            EEPROM24CXX_Internal::address16Bit = true;
            EEPROM24CXX_Internal::blockAddressing = false;

        break;



        case C24C512:

            EEPROM24CXX_Internal::memorySize = 65536;
            EEPROM24CXX_Internal::pageSize = 128;
            EEPROM24CXX_Internal::address16Bit = true;
            EEPROM24CXX_Internal::blockAddressing = false;

        break;



        case C24CM01:

            EEPROM24CXX_Internal::memorySize = 131072;
            EEPROM24CXX_Internal::pageSize = 256;
            EEPROM24CXX_Internal::address16Bit = true;
            EEPROM24CXX_Internal::blockAddressing = false;

        break;



        case C24CM02:

            EEPROM24CXX_Internal::memorySize = 262144;
            EEPROM24CXX_Internal::pageSize = 256;
            EEPROM24CXX_Internal::address16Bit = true;
            EEPROM24CXX_Internal::blockAddressing = false;

        break;



        case C24CM04:

            EEPROM24CXX_Internal::memorySize = 524288;
            EEPROM24CXX_Internal::pageSize = 256;
            EEPROM24CXX_Internal::address16Bit = true;
            EEPROM24CXX_Internal::blockAddressing = false;

        break;



        case C24CM08:

            EEPROM24CXX_Internal::memorySize = 1048576;
            EEPROM24CXX_Internal::pageSize = 256;
            EEPROM24CXX_Internal::address16Bit = true;
            EEPROM24CXX_Internal::blockAddressing = false;

        break;

    }



    Wire.beginTransmission(i2cAddress);



    if(Wire.endTransmission()==0)
    {

        EEPROM24CXX_Internal::initialized = true;


        if(useLed)
            digitalWrite(
                ledPin,
                HIGH
            );

    }

    else
    {

        EEPROM24CXX_Internal::initialized = false;


        if(useLed)
        {

            for(uint8_t i=0;i<5;i++)
            {

                digitalWrite(
                    ledPin,
                    HIGH
                );

                delay(100);


                digitalWrite(
                    ledPin,
                    LOW
                );

                delay(100);

            }

        }

    }

}



// ======================================================
// PUBLIC BYTE FUNCTIONS
// ======================================================

bool writeByte
(
    uint32_t address,
    uint8_t value
)
{

    return EEPROM24CXX_Internal::writeByteRaw
    (
        address,
        value
    );

}



uint8_t readByte
(
    uint32_t address
)
{

    return EEPROM24CXX_Internal::readByteRaw
    (
        address
    );

}



bool updateByte
(
    uint32_t address,
    uint8_t value
)
{

    if(readByte(address)==value)
        return true;


    return writeByte(
        address,
        value
    );

}



// ======================================================
// WRITE PROTECTION
// ======================================================

void lock_mem()
{

    if(
    EEPROM24CXX_Internal::writeProtectPin != 255
    )
    {

        digitalWrite
        (
            EEPROM24CXX_Internal::writeProtectPin,
            HIGH
        );

    }

}



void unlock_mem()
{

    if(
    EEPROM24CXX_Internal::writeProtectPin != 255
    )
    {

        digitalWrite
        (
            EEPROM24CXX_Internal::writeProtectPin,
            LOW
        );

    }

}

// ======================================================
// CURSOR CONTROL
// ======================================================

void mem_seek(uint32_t address)
{
    if(address < EEPROM24CXX_Internal::memorySize)
    {
        EEPROM24CXX_Internal::cursor = address;
    }
}



void rewind()
{
    EEPROM24CXX_Internal::cursor = 0;
}



void skip(uint32_t bytes)
{
    uint32_t pos =
    EEPROM24CXX_Internal::cursor + bytes;


    if(pos <= EEPROM24CXX_Internal::memorySize)
        EEPROM24CXX_Internal::cursor = pos;
}



void mem_back(uint32_t bytes)
{
    if(EEPROM24CXX_Internal::cursor >= bytes)
    {
        EEPROM24CXX_Internal::cursor -= bytes;
    }
}



void mem_end()
{
    EEPROM24CXX_Internal::cursor =
    EEPROM24CXX_Internal::memorySize - 1;
}



uint32_t position()
{
    return EEPROM24CXX_Internal::cursor;
}



uint32_t mem_remaining()
{
    return EEPROM24CXX_Internal::memorySize -
    EEPROM24CXX_Internal::cursor;
}



bool available(uint32_t bytes)
{
    return
    (
        EEPROM24CXX_Internal::cursor + bytes
        <=
        EEPROM24CXX_Internal::memorySize
    );
}



uint8_t peek()
{
    if(!available())
        return 0xFF;


    return EEPROM24CXX_Internal::readByteRaw
    (
        EEPROM24CXX_Internal::cursor
    );
}



// ======================================================
// EEPROM INFORMATION
// ======================================================

uint32_t size()
{
    return EEPROM24CXX_Internal::memorySize;
}



uint16_t pageSize()
{
    return EEPROM24CXX_Internal::pageSize;
}



bool is16Bit()
{
    return EEPROM24CXX_Internal::address16Bit;
}



bool usesBlockAddress()
{
    return EEPROM24CXX_Internal::blockAddressing;
}



// ======================================================
// STRING FUNCTIONS
// ======================================================

void w_str
(
    const String &str
)
{

    for(uint32_t i=0;i<str.length();i++)
    {

        if(!available())
            break;


        writeByte
        (
            EEPROM24CXX_Internal::cursor++,
            str[i]
        );

    }



    if(available())
    {
        writeByte
        (
            EEPROM24CXX_Internal::cursor++,
            0
        );
    }

}



String r_str()
{

    String result;



    while(available())
    {

        char c =
        readByte
        (
            EEPROM24CXX_Internal::cursor++
        );



        if(c == 0)
            break;



        result += c;

    }



    return result;

}



// ======================================================
// BUFFER FUNCTIONS
// ======================================================

void w_bytes
(
    const uint8_t *buffer,
    uint32_t length
)
{

    for(uint32_t i=0;i<length;i++)
    {

        if(!available())
            break;


        writeByte
        (
            EEPROM24CXX_Internal::cursor++,
            buffer[i]
        );

    }

}



void r_bytes
(
    uint8_t *buffer,
    uint32_t length
)
{

    for(uint32_t i=0;i<length;i++)
    {

        if(!available())
            break;


        buffer[i] =
        readByte
        (
            EEPROM24CXX_Internal::cursor++
        );

    }

}



// ======================================================
// RANDOM STRING WRITE
// ======================================================

void overwrite
(
    uint32_t address,
    const String &str
)
{

    for(uint32_t i=0;i<str.length();i++)
    {

        if(address+i >= EEPROM24CXX_Internal::memorySize)
            break;


        writeByte
        (
            address+i,
            str[i]
        );

    }



    if(address+str.length()
    <
    EEPROM24CXX_Internal::memorySize)
    {

        writeByte
        (
            address+str.length(),
            0
        );

    }

}

// ======================================================
// RANDOM ACCESS TEMPLATE SUPPORT
// ======================================================

template<typename T>
void overwrite
(
    uint32_t address,
    const T &value
)
{

    const uint8_t *ptr =
    (const uint8_t *)&value;



    for(size_t i=0;i<sizeof(T);i++)
    {

        if(address+i >= EEPROM24CXX_Internal::memorySize)
            break;



        writeByte
        (
            address+i,
            ptr[i]
        );

    }

}



// ======================================================
// VERIFY DATA
// ======================================================

template<typename T>
bool verify
(
    uint32_t address,
    const T &value
)
{

    const uint8_t *ptr =
    (const uint8_t *)&value;



    for(size_t i=0;i<sizeof(T);i++)
    {

        if(address+i >= EEPROM24CXX_Internal::memorySize)
            return false;



        if(readByte(address+i) != ptr[i])
            return false;

    }



    return true;

}



// ======================================================
// WIPE MEMORY REGION
// ======================================================

void wipe
(
    uint32_t address,
    uint32_t length
)
{

    unlock_mem();



    for(uint32_t i=0;i<length;i++)
    {

        if(address+i >= EEPROM24CXX_Internal::memorySize)
            break;


        writeByte
        (
            address+i,
            0xFF
        );

    }



    lock_mem();

}



// ======================================================
// FILL MEMORY REGION
// ======================================================

void fill
(
    uint32_t address,
    uint32_t length,
    uint8_t value
)
{

    unlock_mem();



    for(uint32_t i=0;i<length;i++)
    {

        if(address+i >= EEPROM24CXX_Internal::memorySize)
            break;


        writeByte
        (
            address+i,
            value
        );

    }



    lock_mem();

}



// ======================================================
// COMPARE MEMORY AREAS
// ======================================================

bool compare
(
    uint32_t address1,
    uint32_t address2,
    uint32_t length
)
{

    for(uint32_t i=0;i<length;i++)
    {

        if(address1+i >= EEPROM24CXX_Internal::memorySize)
            return false;


        if(address2+i >= EEPROM24CXX_Internal::memorySize)
            return false;



        if(
        readByte(address1+i)
        !=
        readByte(address2+i)
        )
        {
            return false;
        }

    }



    return true;

}



// ======================================================
// PRINT EEPROM MEMORY MAP
// ======================================================

void read_all()
{

    Serial.println();
    Serial.println(
    F("------ EEPROM MEMORY ------")
    );



    for(uint32_t i=0;i<EEPROM24CXX_Internal::memorySize;i++)
    {

        if(i%16==0)
        {

            Serial.println();


            if(i<0x10)
                Serial.print("000");

            else if(i<0x100)
                Serial.print("00");

            else if(i<0x1000)
                Serial.print("0");


            Serial.print(i,HEX);
            Serial.print(": ");

        }



        uint8_t value =
        readByte(i);



        if(value<16)
            Serial.print("0");


        Serial.print(value,HEX);
        Serial.print(" ");

    }



    Serial.println();
    Serial.println(
    F("--------------------------")
    );

}



// ======================================================
// WIPE COMPLETE EEPROM
// ======================================================

void wipe_all()
{

    wipe
    (
        0,
        EEPROM24CXX_Internal::memorySize
    );


    EEPROM24CXX_Internal::cursor = 0;

}

