#pragma once

#ifndef _EASY_I2C_H_
#define _EASY_I2C_H_

#include <Wire.h>

namespace easy_i2c {
void Read(TwoWire& wire, const uint8_t i2c_address, const uint8_t mem_address, uint8_t* const buffer, const size_t size);
void Write(TwoWire& wire, const uint8_t i2c_address, const uint8_t mem_address, const uint8_t* const data, const size_t size);

template <typename T>
T Read(TwoWire& wire, const uint8_t i2c_address, const uint8_t mem_address) {
  T value{};
  Read(wire, i2c_address, mem_address, reinterpret_cast<uint8_t*>(&value), sizeof(T));
  return value;
}

template <typename T>
void Write(TwoWire& wire, const uint8_t i2c_address, const uint8_t mem_address, const T& value) {
  Write(wire, i2c_address, mem_address, reinterpret_cast<const uint8_t*>(&value), sizeof(T));
}
}  // namespace easy_i2c

#endif