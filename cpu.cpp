#include "cpu.hpp"

Cpu::Cpu() : memory(_memory) {
    // 6XNN const Vx = NN
    opcode[8] = [](uint16_t _opcode) {
        register[_opcode & 0x0f00] = _opcode & 0x00ff;
    };
    // 7XNN const Vx += NN
    opcode[9] = [](uint16_t _opcode) {
        register[_opcode & 0x0f00] += _opcode & 0x0ff;
    };
    // 8XY0 assign Vx = Vy
    opcode[10] = [](uint16_t _opcode) {
        register[_opcode & 0x0f00] = register[_opcode & 0x00f0];
    };
    // 8XY1 bitop Vx = Vx | Vy
    opcode[11] = [](uint16_t _opcode) {
        register[_opcode & 0x0f00] = register[_opcode & 0x0f00] | register[_opcode & 0x00f0];
    };
    // 8XY2 bitop Vx = Vx & Vy
    opcode[12] = [](uint16_t _opcode) {
        register[_opcode & 0x0f00] = register[_opcode & 0x0f00] & register[_opcode & 0x00f0];
    };
    // 8XY3 bitop Vx = Vx ^ Vy
    opcode[13] = [](uint16_t _opcode) {
        register[_opcode & 0x0f00] = register[_opcode & 0x0f00] ^ register[_opcode & 0x00f0];
    };
    // 8XY4 math Vx += Vy
    opcode[14] = [](uint16_t _opcode) {
        register[_opcode & 0x0f00] += register[_opcode & 0x00f0];
    };
    // 8XY5 math Vx -= Vy
    opcode[15] = [](uint16_t _opcode) {
        register[_opcode & 0x0f00] -= register[_opcode & 0x00f0];
    };
    // 8XY6 bitop Vx >>= Vy
    opcode[16] = [](uint16_t _opcode) {
        register[15] = register[_opcode & 0x0f00] & 1;
        register[_opcode & 0x0f00] >>= 1;
    };
    // 8XY7  math Vx = Vy - Vx
    opcode[17] = [](uint16_t _opcode) {
        register[_opcode & 0x0f00] = register[_opcode & 0x00f0] - register[_opcode & 0x0f00];
    };
    // 8XYE bitop Vx <<= Vy
    opcode[18] = [](uint16_t _opcode) {
        register[15] = register[_opcode & 0x0f00] & (1 << 7);
        register[_opcode & 0x0f00] <<= 1;
    };
}


Cpu::~Cpu() {

}
