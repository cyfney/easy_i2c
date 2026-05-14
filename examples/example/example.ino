#include <Wire.h>

#include "easy_i2c.h"

void setup() {
  Wire.begin();

  // Read uint8_t from I2C device with address 0x40 and memory address 0x10
  uint8_t uint8_read = easy_i2c::Read<uint8_t>(Wire, 0x40, 0x10);

  // Read uint16_t from I2C device with address 0x40 and memory address 0x12
  uint16_t uint16_read = easy_i2c::Read<uint16_t>(Wire, 0x40, 0x12);

  // Read uint32_t from I2C device with address 0x40 and memory address 0x10
  uint32_t uint32_read = easy_i2c::Read<uint32_t>(Wire, 0x40, 0x10);

  // Read int32_t from I2C device with address 0x40 and memory address 0x20
  int32_t int32_read = easy_i2c::Read<int32_t>(Wire, 0x40, 0x20);

  // Read buffer from I2C device with address 0x40 and memory address 0x10
  uint8_t buffer_read[3] = {0};
  easy_i2c::Read(Wire, 0x40, 0x10, buffer_read, sizeof(buffer_read));

  // Write uint8_t to I2C device with address 0x40 and memory address 0x10
  uint8_t uint8_write = 0x10;
  easy_i2c::Write(Wire, 0x40, 0x10, uint8_write);

  // Write uint16_t to I2C device with address 0x40 and memory address 0x12
  uint16_t uint16_write = 0x1234;
  easy_i2c::Write(Wire, 0x40, 0x12, uint16_write);

  // Write uint32_t to I2C device with address 0x40 and memory address 0x10
  uint32_t uint32_write = 0x12345678;
  easy_i2c::Write(Wire, 0x40, 0x10, uint32_write);

  // Write int32_t to I2C device with address 0x40 and memory address 0x20
  int32_t int32_write = 0x12345678;
  easy_i2c::Write(Wire, 0x40, 0x20, int32_write);

  // Write buffer to I2C device with address 0x40 and memory address 0x10
  uint8_t buffer_write[3] = {0x10, 0x20, 0x30};
  easy_i2c::Write(Wire, 0x40, 0x10, buffer_write, sizeof(buffer_write));
}

void loop() {}