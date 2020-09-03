#pragma once

#include <stdint.h>
#include <functional>

class Cpu {

private:
    std::function<void(uint16_t)>* opcode[35];
    uint8_t register[16];
    uint16_t I;
    uint PC;

    Memory* memory;
    
public:
    Cpu();
    ~Cpu();
};