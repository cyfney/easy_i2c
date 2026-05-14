# Easy I2C Arduino Lib

A lightweight and easy-to-use C++ library designed to simplify I2C communication on the Arduino platform.

## Features

- **Template-based API**: Directly read and write standard C++ data types (uint8_t, int32_t, float, structs, etc.) without manual byte manipulation.

- **Buffer Support**: Includes low-level functions for reading and writing raw byte arrays.

- **Minimalist**: Wraps the standard Wire(TwoWire) library to reduce boilerplate code and improve readability.

- **Endian-Aware**: Automatically handles data conversion (Little Endian) when writing multi-byte types.

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

  // Read a single byte
  uint8_t reg_val = easy_i2c::Read<uint8_t>(Wire, 0x40, 0x10);

  // Read a 32-bit integer
  int32_t large_val = easy_i2c::Read<int32_t>(Wire, 0x40, 0x20);

  // Read raw bytes into a buffer
  uint8_t buffer[3];
  easy_i2c::Read(Wire, 0x40, 0x10, buffer, sizeof(buffer));
}

void loop() {
}
```

### Writing Data

The library handles the low-level transmission automatically. Note that multi-byte values are stored in **Little Endian**​ format.

```c++
#include <Wire.h>
#include "easy_i2c.h"

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Write a single byte
  easy_i2c::Write(Wire, 0x40, 0x10, static_cast<uint8_t>(0x10));

  // Write a 16-bit value
  // Memory[0x12] = 0x34, Memory[0x13] = 0x12
  easy_i2c::Write(Wire, 0x40, 0x12, static_cast<uint16_t>(0x1234));

  // Write a buffer
  uint8_t data[3] = {0x10, 0x20, 0x30};
  easy_i2c::Write(Wire, 0x40, 0x10, data, sizeof(data));
}

void loop() {
}
```

## Note on Endianness

This library writes multi-byte data (such as `uint16_t` or `uint32_t`) in Little Endian​ format to match the native memory layout of most microcontrollers.

- Example:Writing `0x12345678` to address `0x10` results in:
  - [0x10] = 0x78
  - [0x11] = 0x56
  - [0x12] = 0x34
  - [0x13] = 0x12
