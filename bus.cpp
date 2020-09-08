#include "bus.hpp"

Bus::Bus(Memory* _memory) : memory(_memory) {}

Bus::~Bus() {

}

uint8_t
Bus::FetchFrom(uint16_t _address) {
    return memory->LoadFrom(_address);
}

void
Bus::SendTo(uint16_t _address, uint8_t _data) {
    memory->StoreTo(_address, _data);
}