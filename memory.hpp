#pragma once

#include <stdint.h>

#define MEMORY_SIZE 4096 

class Memory {

private:
    uint8_t memory[MEMORY_SIZE];

public:
    Memory();
    ~Memory();

    void        StoreTo(uint16_t _address, uint8_t _data);
    uint8_t     LoadFrom(uint16_t _address);
};

