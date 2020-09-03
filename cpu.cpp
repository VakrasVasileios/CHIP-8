#include "cpu.hpp"
#include <stdlib.h>

Cpu::Cpu() : memory(_memory), I(0), PC(0){

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
        register[15] = register[_opcode & 0x0f00] & 1;          // store least significant bit to VF
        register[_opcode & 0x0f00] >>= 1;
    };
    // 8XY7  math Vx = Vy - Vx
    opcode[17] = [](uint16_t _opcode) {
        register[_opcode & 0x0f00] = register[_opcode & 0x00f0] - register[_opcode & 0x0f00];
    };
    // 8XYE bitop Vx <<= Vy
    opcode[18] = [](uint16_t _opcode) {
        register[15] = register[_opcode & 0x0f00] & (1 << 7);   // store most significant bit to VF
        register[_opcode & 0x0f00] <<= 1;
    };
    // 9XY0 cond if(Vx != Vy)

    // ANNN mem I = NNN
    opcode[20] = [](uint16_t _opcode) {
        I = _opcode & 0X0FFF;
    };
    // BNNN flow PC = V0 + NNN
    opcode[21] = [](uint16_t _opcode) {
        PC = register[0] + (_opcode & 0x0FFF);
    };
    // CXNN rand Vx = rand() & NN
    opcode[22] = [](uint16_t _opcode) {
        register[_opcode & 0x0F00] = (rand() % 256) & (_opcode & 0x00FF);
    };
}


Cpu::~Cpu() {

}
