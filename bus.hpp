#pragma once

#include "memory.hpp"
#include "display.hpp"

class Bus {

private:
    Memory* memory;
    Display* display;
public:
    Bus(Memory* _memory, Display* _display);
    ~Bus();

    uint8_t    FetchFrom(uint16_t _address);
    void       SendTo(uint16_t _address, uint8_t _data);
    void       ClearDisplay();
};

