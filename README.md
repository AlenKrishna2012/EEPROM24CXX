# EEPROM24CXX Library

An Arduino I2C EEPROM library for external 24Cxx and 24CMxx EEPROM chips.

Supports simple byte access, strings, arrays, structures, data logging, memory utilities, and hardware write protection.

---

# Supported EEPROM Chips

- 24C01
- 24C02
- 24C04
- 24C08
- 24C16
- 24C32
- 24C64
- 24C128
- 24C256
- 24C512
- 24CM01
- 24CM02
- 24CM04
- 24CM08

---

# Features

- Old Arduino style API
- No object creation required
- AVR / ESP8266 / ESP32 compatible
- I2C communication
- Byte read and write
- Update only changed data
- Cursor based sequential access
- String storage
- Buffer storage
- Any datatype storage
- Structure storage
- EEPROM erase
- EEPROM fill
- Memory comparison
- EEPROM memory dump
- Hardware write protection

---

# Installation

Copy the library folder:

```
EEPROM24CXX
```

into:

```
Arduino/libraries/
```

Restart Arduino IDE.

---

# Library Structure

```
EEPROM24CXX
│
├── src
│   ├── EEPROM24CXX.h
│   └── EEPROM24CXX.cpp
│
├── examples
│   ├── 01_Basic_Read_Write
│   ├── 02_Update_Byte
│   ├── 03_String_Storage
│   ├── 04_Struct_Storage
│   ├── 05_Buffer_Read_Write
│   ├── 06_EEPROM_Dump
│   ├── 07_EEPROM_Erase
│   ├── 08_Write_Protection
│   ├── 09_Memory_Compare
│   └── 10_Data_Logger
│
├── library.properties
├── keywords.txt
└── README.md
```

---

# Include Library

```cpp
#include <EEPROM24CXX.h>
```

---

# Initialization

## mem_init()

Initialize EEPROM.

### Syntax

```cpp
mem_init(type, i2cAddress, wpPin, ledPin, useLed);
```

### Example

```cpp
mem_init(C24C02);
```

### Advanced Example

```cpp
mem_init(C24C02,0x50,5,13,true);
```

Default settings:

```cpp
mem_init(C24C02);
```

Custom I2C address:

```cpp
mem_init(C24C02,0x51);
```

With write protection:

```cpp
mem_init(C24C02,0x50,5);
```

With LED status:

```cpp
mem_init(C24C02,0x50,5,13,true);
```
---

# EEPROM Types

```cpp
C24C01
C24C02
C24C04
C24C08
C24C16
C24C32
C24C64
C24C128
C24C256
C24C512
C24CM01
C24CM02
C24CM04
C24CM08
```

---

# Byte Functions

## writeByte()

Write one byte.

### Syntax

```cpp
writeByte(address,value);
```

Example:

```cpp
writeByte(10,255);
```

---

## readByte()

Read one byte.

### Syntax

```cpp
uint8_t value = readByte(address);
```

Example:

```cpp
byte data = readByte(10);
```

---

## updateByte()

Write only if data changed.

```cpp
updateByte(address,value);
```

Example:

```cpp
updateByte(10,50);
```

---

# Cursor Functions

## mem_seek()

Move cursor.

```cpp
mem_seek(address);
```

---

## rewind()

Move cursor to beginning.

```cpp
rewind();
```

---

## skip()

Move cursor forward.

```cpp
skip(bytes);
```

---

## mem_back()

Move cursor backward.

```cpp
mem_back(bytes);
```

---

## mem_end()

Move cursor to last byte.

```cpp
mem_end();
```

---

## position()

Get cursor position.

```cpp
uint32_t pos = position();
```

---

## mem_remaining()

Get remaining memory.

```cpp
uint32_t bytes = mem_remaining();
```

---

## available()

Check available memory.

```cpp
if(available(20))
{
}
```

---

## peek()

Read current byte without moving cursor.

```cpp
byte value = peek();
```

---

# Information Functions

## size()

Get EEPROM size.

```cpp
uint32_t bytes = size();
```

---

## pageSize()

Get page size.

```cpp
uint16_t page = pageSize();
```

---

## is16Bit()

Check 16-bit addressing.

```cpp
bool result = is16Bit();
```

---

## usesBlockAddress()

Check block addressing.

```cpp
bool result = usesBlockAddress();
```

---

# Sequential Data Functions

## write()

Write any datatype.

```cpp
write(variable);
```

Example:

```cpp
int number = 123;

write(number);
```

---

## read()

Read any datatype.

```cpp
read(variable);
```

Example:

```cpp
int number;

read(number);
```

---

## update()

Update datatype.

```cpp
update(variable);
```

---

# String Functions

## w_str()

Write String.

```cpp
w_str("Hello EEPROM");
```

---

## r_str()

Read String.

```cpp
String text = r_str();
```

---

# Buffer Functions

## w_bytes()

Write byte array.

```cpp
w_bytes(buffer,length);
```

Example:

```cpp
uint8_t data[]={1,2,3};

w_bytes(data,3);
```

---

## r_bytes()

Read byte array.

```cpp
r_bytes(buffer,length);
```

Example:

```cpp
uint8_t data[3];

r_bytes(data,3);
```

---

# Random Access Functions

## overwrite()

Write data at address.

```cpp
overwrite(address,value);
```

Example:

```cpp
float voltage=3.3;

overwrite(100,voltage);
```

Write String:

```cpp
overwrite(100,"Text");
```

---

## verify()

Verify stored data.

```cpp
verify(address,value);
```

Example:

```cpp
if(verify(100,voltage))
{
    Serial.println("Correct");
}
```

---

# Memory Utility Functions

## wipe()

Erase memory area.

```cpp
wipe(address,length);
```

Example:

```cpp
wipe(0,100);
```

---

## wipe_all()

Erase complete EEPROM.

```cpp
wipe_all();
```

---

## fill()

Fill memory.

```cpp
fill(address,length,value);
```

Example:

```cpp
fill(0,100,0xAA);
```

---

## compare()

Compare two memory areas.

```cpp
compare(address1,address2,length);
```

Example:

```cpp
compare(0,100,20);
```

---

# Debug Functions

## read_all()

Print EEPROM memory map.

```cpp
read_all();
```

Example output:

```
0000: FF FF 01 02 03
0010: AA AA AA AA
```

---

# Write Protection

## lock_mem()

Enable write protection.

```cpp
lock_mem();
```

---

## unlock_mem()

Disable write protection.

```cpp
unlock_mem();
```

---

# Basic Example

```cpp
#include <EEPROM24CXX.h>


void setup()
{
    Serial.begin(115200);

    mem_init(C24C02);

    writeByte(0,123);

    Serial.println(
        readByte(0)
    );


    mem_seek(10);

    w_str("Hello");


    mem_seek(10);

    Serial.println(
        r_str()
    );
}


void loop()
{

}
```

---

# License

MIT License
