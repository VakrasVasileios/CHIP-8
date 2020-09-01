#pragma once

#include <stdint.h>

#define MEMORY_SIZE 4096
#define PROGRAM_LOCATION 512
#define DISPLAY_REFRESH_LOCATION 778
#define STACK_LOCATION 682

class Memory {

private:
    uint8_t memory[MEMORY_SIZE];
    uint8_t stack_pointer = 0;

public:
    Memory();
    ~Memory();

    uint8_t*    GetProgram();
    void        IncreaseStackPointer() { stack_pointer++; }
    uint8_t*    GetStack();
    uint8_t*    GetDisplayRefresh();
};

