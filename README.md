# Easy I2C Arduino Lib

A lightweight and easy-to-use C++ library designed to simplify I2C communication on the Arduino platform.

## Features

- **Template-based API**: Directly read and write standard C++ data types (uint8_t, int32_t, float, structs, etc.) without manual byte manipulation.

- **Buffer Support**: Includes low-level functions for reading and writing raw byte arrays.

- **Minimalist**: Wraps the standard Wire(TwoWire) library to reduce boilerplate code and improve readability.

- **Endian-Aware**: Automatically handles data conversion (Little Endian) when writing multi-byte types.

- **Dual Address Width**: Supports both 8-bit (default) and 16-bit (`wide` namespace) register/memory addresses for compatibility with sensors, EEPROMs, and FRAMs.

## Usage

Include the header and utilize the `easy_i2c` namespace.

### Reading Data

Read specific types directly using template functions:

```c++
#include <Wire.h>
#include "easy_i2c.h"

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Read a single byte from register/memory address 0x10
  uint8_t reg_val = easy_i2c::Read<uint8_t>(Wire, 0x40, 0x10);

  // Read a 32-bit integer from register/memory address 0x20
  int32_t large_val = easy_i2c::Read<int32_t>(Wire, 0x40, 0x20);

  // Read raw bytes into a buffer from register/memory address 0x10
  uint8_t buffer[3];
  easy_i2c::Read(Wire, 0x40, 0x10, buffer, sizeof(buffer));
}

void loop() {
}
```

### Writing Data

The library handles the low-level transmission automatically. Note that multi-byte values are stored in **Little Endian** format.

```c++
#include <Wire.h>
#include "easy_i2c.h"

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Write a single byte to register/memory address 0x10
  easy_i2c::Write(Wire, 0x40, 0x10, static_cast<uint8_t>(0x10));

  // Write a 16-bit value to register/memory address 0x12
  // Memory[0x12] = 0x34, Memory[0x13] = 0x12
  easy_i2c::Write(Wire, 0x40, 0x12, static_cast<uint16_t>(0x1234));

  // Write a buffer to register/memory address 0x10
  uint8_t data[3] = {0x11, 0x22, 0x33};
  easy_i2c::Write(Wire, 0x40, 0x10, data, sizeof(data));
}

void loop() {
}
```

### Using Wide Address (16-bit)

For devices that require 16-bit register/memory addresses (like EEPROM or FRAM), use the `wide` namespace.

```c++
#include <Wire.h>
#include "easy_i2c_wide.h"

void setup() {
  Wire.begin();
  
  // Read a byte from EEPROM at 16-bit register/memory address 0x1234
  uint8_t eeprom_data = easy_i2c::wide::Read<uint8_t>(Wire, 0x50, 0x1234);

  // Write a 32-bit value to EEPROM at 16-bit register/memory address 0x5678
  easy_i2c::wide::Write<uint32_t>(Wire, 0x50, 0x5678, static_cast<uint32_t>(0xDEADBEEF));
}
void loop() {
}
```

## Note on Endianness

This library writes multi-byte data (such as `uint16_t` or `uint32_t`) in Little Endian format to match the native memory layout of most microcontrollers.

- Example:Writing `0x12345678` to address `0x10` results in:
  - [0x10] = 0x78
  - [0x11] = 0x56
  - [0x12] = 0x34
  - [0x13] = 0x12
