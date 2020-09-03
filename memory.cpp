#include "memory.hpp"

Memory::Memory() {

}

Memory::~Memory() {

}

uint8_t*
Memory::GetProgram() {
    return &(memory+(PROGRAM_LOCATION-1));
}

uint8_t* 
Memory::GetStack() {
    return &(memory+stack_pointer+(STACK_LOCATION-1));
}

uint8_t*
Memory::GetDisplayRefresh() {
    return &(memory+(DISPLAY_REFRESH_LOCATION-1));
}

void
Memory::ChangeSP(int num) {
    stack_pointer += num;
}

void
Memory::StoreTo(uint16_t _address, uint8_t _data) {
    memory[_address] = _data;
}

uint8_t
Memory::LoadFrom(uint16_t _address) {
    return memory[_address];
}