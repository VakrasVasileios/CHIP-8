#pragma once

#include <stdint.h>
#include <functional>

class Cpu {

private:
    std::function<void(uint16_t)>* opcode[35];
    uint8_t register[16];
    Memory* memory;
    
public:
    Cpu();
    ~Cpu();
};