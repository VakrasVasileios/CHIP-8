#include "memory.hpp"

Memory::Memory() {

}

Memory::~Memory() {

}

uint8_t*
Memory::GetProgram() {
    return memory+(PROGRAM_LOCATION-1);
}

uint8_t* 
Memory::GetStack() {
    return memory+stack_pointer+(STACK_LOCATION-1);
}

uint8_t* 
Memory::GetDisplayRefresh() {
    return memory+(DISPLAY_REFRESH_LOCATION-1);
}