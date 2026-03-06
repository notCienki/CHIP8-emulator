#include "chip8.h"
#include <fstream>

const unsigned int START_ADDRESS = 0x200;
const unsigned int FONTSET_START_ADDRESS = 0x50;
const unsigned int FONTSET_SIZE = 80;

uint8_t fontset[FONTSET_SIZE] =
    {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

Chip8::Chip8()
{
  pc = START_ADDRESS;

  for (int i = 0; i < FONTSET_SIZE; i++)
  {
    memory[FONTSET_START_ADDRESS + i] = fontset[i];
  }
}

void Chip8::LoadROM(char const *filename)
{
  std::ifstream file(filename, std::ios::binary | std::ios::ate);
  if (file.is_open())
  {
    std::streampos size = file.tellg();
    char *buffer = new char[size];
    file.seekg(0, std::ios::beg);
    file.read(buffer, size);
    file.close();
    for (long i = 0; i < size; ++i)
    {
      memory[START_ADDRESS + i] = buffer[i];
    }
    delete[] buffer;
  }
}

void Chip8::Cycle()
{
  opcode = (memory[pc] << 8) | memory[pc + 1];
  pc += 2;
  uint8_t firstNumber = (opcode & 0xF000) >> 12;

  switch (firstNumber)
  {
  case 0x1:
  {
    uint16_t address = opcode & 0x0FFF;
    pc = address;
    break;
  }
  case 0x6:
  {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t kk = opcode & 0x00FF;
    registers[x] = kk;
    break;
  }
  case 0x7:
  {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t kk = opcode & 0x00FF;
    registers[x] += kk;
    break;
  }
  case 0x8:
  {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x00F0) >> 4;
    uint8_t lastNumber = (opcode & 0x000F);
    switch (lastNumber)
    {
    case 0x0:
    {
      registers[x] = registers[y];
      break;
    }
    }
    break;
  }
  default:
    break;
  }
}