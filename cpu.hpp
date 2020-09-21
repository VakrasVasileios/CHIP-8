#pragma once

#include <stdint.h>
#include <functional>
#include "bus.hpp"



class Cpu {

private:
    std::function<void(uint16_t)>* opcode[34];

    uint8_t     v[16];              // 16 8bit registers
    uint16_t    I = 0;              // 16bit register for memory address
    uint16_t    PC = 0;             // program counter
    uint        sp = 0;             // stack pointer (index)
    uint16_t    stack[12];

    Bus         bus;

    uint16_t    PopStack();
    void        InsertToStack(uint16_t _address);

public:
    Cpu(Memory* _memory, Display* _display);
    ~Cpu();
};