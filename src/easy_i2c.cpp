#include "easy_i2c.h"

namespace easy_i2c {
void Read(TwoWire& wire, const uint8_t i2c_address, const uint8_t mem_address, uint8_t* const buffer, const size_t size) {
  wire.beginTransmission(i2c_address);
  wire.write(mem_address);
  if (0 != wire.endTransmission()) {
    abort();
  }

  wire.requestFrom(i2c_address, size);

  size_t offset = 0;

  while (offset < size) {
    offset += wire.readBytes(buffer + offset, size - offset);
  }
}

void Write(TwoWire& wire, const uint8_t i2c_address, const uint8_t mem_address, const uint8_t* const data, const size_t size) {
  wire.beginTransmission(i2c_address);
  wire.write(mem_address);
  wire.write(data, size);
  if (0 != wire.endTransmission()) {
    abort();
  }
}
}  // namespace easy_i2c