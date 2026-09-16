#ifndef EEPROM24CXX_H
#define EEPROM24CXX_H

#include <Arduino.h>
#include <Wire.h>


// ======================================================
// EEPROM24CXX Library
// Old Style Global API
//
// Supported:
// 24C01
// 24C02
// 24C04
// 24C08
// 24C16
// 24C32
// 24C64
// 24C128
// 24C256
// 24C512
// 24CM01
// 24CM02
// 24CM04
// 24CM08
// ======================================================



// ======================================================
// EEPROM TYPES
// ======================================================

enum EEPROMType
{
    C24C01,
    C24C02,
    C24C04,
    C24C08,
    C24C16,

    C24C32,
    C24C64,
    C24C128,
    C24C256,
    C24C512,

    C24CM01,
    C24CM02,
    C24CM04,
    C24CM08
};



// ======================================================
// INITIALIZATION
// ======================================================

void mem_init
(
    EEPROMType type,
    uint8_t i2cAddress = 0x50,
    uint8_t wpPin = 255,
    uint8_t ledPin = 13,
    bool useLed = false
);



// ======================================================
// BASIC BYTE ACCESS
// ======================================================

bool writeByte
(
    uint32_t address,
    uint8_t value
);


uint8_t readByte
(
    uint32_t address
);


bool updateByte
(
    uint32_t address,
    uint8_t value
);



// ======================================================
// WRITE PROTECTION
// ======================================================

void lock_mem();

void unlock_mem();



// ======================================================
// CURSOR CONTROL
// ======================================================

void mem_seek
(
    uint32_t address
);


void rewind();


void skip
(
    uint32_t bytes
);


void mem_back
(
    uint32_t bytes
);


void mem_end();


uint32_t position();


uint32_t mem_remaining();


bool available
(
    uint32_t bytes = 1
);


uint8_t peek();



// ======================================================
// EEPROM INFORMATION
// ======================================================

uint32_t size();

uint16_t pageSize();

bool is16Bit();

bool usesBlockAddress();



// ======================================================
// SEQUENTIAL DATA ACCESS
// ======================================================

template<typename T>
void write
(
    const T &value
);



template<typename T>
void read
(
    T &value
);



template<typename T>
void update
(
    const T &value
);



// ======================================================
// STRING FUNCTIONS
// ======================================================

void w_str
(
    const String &str
);


String r_str();



// ======================================================
// BUFFER FUNCTIONS
// ======================================================

void w_bytes
(
    const uint8_t *buffer,
    uint32_t length
);


void r_bytes
(
    uint8_t *buffer,
    uint32_t length
);



// ======================================================
// RANDOM ACCESS
// ======================================================

template<typename T>
void overwrite
(
    uint32_t address,
    const T &value
);



void overwrite
(
    uint32_t address,
    const String &str
);



template<typename T>
void read
(
    uint32_t address,
    T &value
);



template<typename T>
bool verify
(
    uint32_t address,
    const T &value
);

// ======================================================
// MEMORY UTILITIES
// ======================================================

// Fill memory region with 0xFF
void wipe
(
    uint32_t address,
    uint32_t length
);


// Fill memory region with custom value
void fill
(
    uint32_t address,
    uint32_t length,
    uint8_t value
);


// Compare two EEPROM regions
bool compare
(
    uint32_t address1,
    uint32_t address2,
    uint32_t length
);



// ======================================================
// COMPLETE MEMORY OPERATIONS
// ======================================================

// Erase complete EEPROM
void wipe_all();


// Print EEPROM contents
void read_all();



// ======================================================
// INTERNAL CONFIGURATION
// ======================================================

namespace EEPROM24CXX_Internal
{

    extern uint8_t deviceAddress;

    extern uint8_t writeProtectPin;


    extern uint32_t memorySize;


    extern uint16_t pageSize;


    extern bool address16Bit;


    extern bool blockAddressing;


    extern uint32_t cursor;


    extern bool initialized;



    // Low level functions

    bool writeByteRaw
    (
        uint32_t address,
        uint8_t value
    );


    uint8_t readByteRaw
    (
        uint32_t address
    );


    uint8_t getDeviceAddress
    (
        uint32_t address
    );


    bool waitReady
    (
        uint32_t timeout = 50
    );


    bool checkAddress
    (
        uint32_t address,
        uint32_t length = 1
    );


    bool writePage
    (
        uint32_t address,
        const uint8_t *buffer,
        uint16_t length
    );

}

// ======================================================
// TEMPLATE IMPLEMENTATIONS
// ======================================================


// ------------------------------------------------------
// Sequential write
// Cursor automatically moves forward
// ------------------------------------------------------

template<typename T>
void write
(
    const T &value
)
{

    const uint8_t *ptr =
    (const uint8_t *)&value;


    for(size_t i = 0; i < sizeof(T); i++)
    {

        if(!available())
            break;


        EEPROM24CXX_Internal::writeByteRaw
        (
            EEPROM24CXX_Internal::cursor++,
            ptr[i]
        );

    }

}



// ------------------------------------------------------
// Sequential read
// Cursor automatically moves forward
// ------------------------------------------------------

template<typename T>
void read
(
    T &value
)
{

    uint8_t *ptr =
    (uint8_t *)&value;


    for(size_t i = 0; i < sizeof(T); i++)
    {

        if(!available())
            break;


        ptr[i] =
        EEPROM24CXX_Internal::readByteRaw
        (
            EEPROM24CXX_Internal::cursor++
        );

    }

}



// ------------------------------------------------------
// Sequential update
// Writes only changed bytes
// ------------------------------------------------------

template<typename T>
void update
(
    const T &value
)
{

    const uint8_t *ptr =
    (const uint8_t *)&value;



    for(size_t i = 0; i < sizeof(T); i++)
    {

        if(!available())
            break;



        uint32_t addr =
        EEPROM24CXX_Internal::cursor++;



        if(
        EEPROM24CXX_Internal::readByteRaw(addr)
        != ptr[i])
        {

            EEPROM24CXX_Internal::writeByteRaw
            (
                addr,
                ptr[i]
            );

        }

    }

}



// ------------------------------------------------------
// Random write any datatype
// ------------------------------------------------------

template<typename T>
void overwrite
(
    uint32_t address,
    const T &value
)
{

    const uint8_t *ptr =
    (const uint8_t *)&value;



    for(size_t i = 0; i < sizeof(T); i++)
    {

        if(!EEPROM24CXX_Internal::checkAddress
        (
            address+i
        ))
            break;



        EEPROM24CXX_Internal::writeByteRaw
        (
            address+i,
            ptr[i]
        );

    }

}



// ------------------------------------------------------
// Verify stored datatype
// ------------------------------------------------------

template<typename T>
bool verify
(
    uint32_t address,
    const T &value
)
{

    const uint8_t *ptr =
    (const uint8_t *)&value;



    for(size_t i = 0; i < sizeof(T); i++)
    {

        if(
        EEPROM24CXX_Internal::readByteRaw
        (
            address+i
        )
        != ptr[i])
        {
            return false;
        }

    }


    return true;

}

// ======================================================
// COMPATIBILITY HELPERS
// ======================================================


// Check if EEPROM library is initialized
#define EEPROM24CXX_READY() \
    (EEPROM24CXX_Internal::initialized)



#endif