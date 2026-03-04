#ifndef CHIP8_H
#define CHIP8_H

#include <cstdint>

class Chip8
{
public:
  Chip8();

private:
  uint8_t memory[4096]{};
  uint8_t registers[16]{};
  uint16_t index{};
  uint16_t pc{};
  uint16_t stack[16]{};
  uint8_t sp{};
  uint8_t delayTimer{};
  uint8_t soundTimer{};
  uint16_t opcode{};
};

#endif
