#pragma once

#include <stdint.h>
#include <functional>
#include "bus.hpp"

class Cpu {

private:
    std::function<void(uint16_t)>* opcode[34];

    uint8_t     registers[16];
    uint16_t    I = 0;              // 16bit register for memory address
    uint        PC = 0;             // program counter
    uint        sp = 0;             // stack pointer index

    Bus         bus;

public:
    Cpu(Memory* _memory, Display* _display);
    ~Cpu();
};