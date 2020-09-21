#include "memory.hpp"

Memory::Memory() {

}

Memory::~Memory() {

}

void
Memory::StoreTo(uint16_t _address, uint8_t _data) {
    memory[_address] = _data;
}

uint8_t
Memory::LoadFrom(uint16_t _address) {
    return memory[_address];
}