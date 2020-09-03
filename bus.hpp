#pragma once

#include "memory.hpp"

class Bus {

private:
    Memory* memory;
public:
    Bus();
    ~Bus();

    uint8_t    FetchFrom(uint16_t _address);
    void       SendTo(uint16_t _address, uint8_t _data);
};

