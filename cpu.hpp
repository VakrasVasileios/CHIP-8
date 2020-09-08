#pragma once

#include <stdint.h>
#include <functional>
#include "bus.hpp"

class Cpu {

private:
    std::function<void(uint16_t)>* opcode[35];

    uint8_t     registers[16];
    uint16_t    I = 0;
    uint        PC = 0;

    Bus         bus;
    
public:
    Cpu(Memory* _memory);
    ~Cpu();
};