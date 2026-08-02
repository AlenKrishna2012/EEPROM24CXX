# EEPROM24CXX Library

A lightweight Arduino library for AT24CXX I²C EEPROMs with automatic device configuration, sequential memory access, and built-in diagnostic utilities.

## Supported EEPROMs

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

---

# Features

## Automatic Device Configuration

Automatically configures:

- EEPROM size
- Page size
- Addressing mode (8-bit or 16-bit)
- Block addressing (24C04/08/16)

using a single initialization function.

---

## I²C Communication

- Automatic 8-bit addressing
- Automatic 16-bit addressing
- Automatic block addressing support
- Supports custom I²C device addresses

---

## Sequential Memory Access

Built-in memory cursor for automatic sequential operations.

Functions:

```cpp
w_int()
r_int()

w_str()
r_str()

mem_seek()
mem_tell()
```

---

## Integer Storage

Store and retrieve 32-bit signed integers.

```cpp
w_int(value);

long value = r_int();
```

---

## String Storage

Store and retrieve Arduino `String` objects.

Strings are automatically terminated with `'\0'`.

```cpp
w_str("Hello");

String text = r_str();
```

---

## Random Address Writing

Overwrite data at any EEPROM address without changing the current cursor.

```cpp
overwrite(address, value);

overwrite(address, text);
```

Supports:

- Integer
- String

---

## Memory Navigation

Move or read the current EEPROM cursor.

```cpp
mem_seek(address);

mem_tell();
```

---

## Write Protect Control

Control the EEPROM Write Protect (WP) pin.

```cpp
unlock_mem();

lock_mem();
```

---

## Automatic Bounds Protection

Prevents writing or reading beyond the EEPROM capacity.

---

## EEPROM Initialization

Simple initialization function.

```cpp
mem_init(
    EEPROMType type,
    uint8_t i2cAddress = 0x50,
    uint8_t wpPin = 255,
    uint8_t ledPin = 13,
    bool useLed = false
);
```

Features:

- Starts Serial
- Starts I²C
- Detects EEPROM connection
- Configures device parameters
- Initializes optional Write Protect pin
- Optional status LED

---

## EEPROM Detection

Reports device connection status through the Serial Monitor.

```
Connected
```

or

```
Error
```

---

## Memory Dump

Prints the complete EEPROM contents in hexadecimal format.

```cpp
read_all();
```

Example:

```
0000: FF FF FF FF FF FF FF FF ...
0010: 48 65 6C 6C 6F 00 FF FF ...
```

---

## Memory Erase

Erase the entire EEPROM by writing `0xFF` to every memory location.

```cpp
wipe_all();
```

Features:

- Automatically unlocks EEPROM
- Clears all memory
- Resets memory cursor
- Restores Write Protect

---

## Internal Features

- Automatic cursor management
- Automatic memory size detection
- Automatic page size configuration
- Automatic addressing mode selection
- Automatic block address selection
- Safe memory boundary checking
- Configurable write protect pin
- Configurable status LED
- Configurable I²C address

---

# Included Functions

```cpp
mem_init()

w_int()
r_int()

w_str()
r_str()

overwrite()

mem_seek()
mem_tell()

lock_mem()
unlock_mem()

read_all()

wipe_all()
```

---

# Requirements

- Arduino IDE/ArduinoDroid
- Wire library
- AT24CXX I²C EEPROM