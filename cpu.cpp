#include <stdlib.h>
#include "cpu.hpp"

Cpu::Cpu(Memory* _memory) {
    bus = Bus(_memory);

    // 6XNN const Vx = NN
    opcode[8] = [&registers](uint16_t _opcode) {
        registers[(_opcode & 0x0f00)] = _opcode & 0x00ff;
    };
    // 7XNN const Vx += NN
    opcode[9] = [&registers](uint16_t _opcode) {
        registers[(_opcode & 0x0f00)] += _opcode & 0x0ff;
    };
    // 8XY0 assign Vx = Vy
    opcode[10] = [&registers](uint16_t _opcode) {
        registers[(_opcode & 0x0f00)] = registers[(_opcode & 0x00f0)];
    };
    // 8XY1 bitop Vx = Vx | Vy
    opcode[11] = [&registers](uint16_t _opcode) {
        registers[(_opcode & 0x0f00)] = registers[(_opcode & 0x0f00)] | registers[(_opcode & 0x00f0)];
    };
    // 8XY2 bitop Vx = Vx & Vy
    opcode[12] = [&registers](uint16_t _opcode) {
        registers[(_opcode & 0x0f00)] = registers[(_opcode & 0x0f00)] & registers[(_opcode & 0x00f0)];
    };
    // 8XY3 bitop Vx = Vx ^ Vy
    opcode[13] = [&registers](uint16_t _opcode) {
        registers[(_opcode & 0x0f00)] = registers[(_opcode & 0x0f00)] ^ registers[(_opcode & 0x00f0)];
    };
    // 8XY4 math Vx += Vy
    opcode[14] = [&registers](uint16_t _opcode) {
        registers[(_opcode & 0x0f00)] += registers[(_opcode & 0x00f0)];
    };
    // 8XY5 math Vx -= Vy
    opcode[15] = [&registers](uint16_t _opcode) {
        registers[(_opcode & 0x0f00)] -= registers[(_opcode & 0x00f0)];
    };
    // 8XY6 bitop Vx >>= Vy
    opcode[16] = [&registers](uint16_t _opcode) {
        registers[15] = registers[(_opcode & 0x0f00)] & 1;          // store least significant bit to VF
        registers[(_opcode & 0x0f00)] >>= 1;
    };
    // 8XY7  math Vx = Vy - Vx
    opcode[17] = [&registers](uint16_t _opcode) {
        registers[(_opcode & 0x0f00)] = registers[(_opcode & 0x00f0)] - registers[(_opcode & 0x0f00)];
    };
    // 8XYE bitop Vx <<= Vy
    opcode[18] = [&registers](uint16_t _opcode) {
        registers[15] = registers[(_opcode & 0x0f00)] & (1 << 7);   // store most significant bit to VF
        registers[(_opcode & 0x0f00)] <<= 1;
    };
    // 9XY0 cond if(Vx != Vy)

    // ANNN mem I = NNN
    opcode[20] = [&, registers, I](uint16_t _opcode) {
        I = _opcode & 0X0fff
    };
    // BNNN flow PC = V0 + NNN
    opcode[21] = [&, registers, PC](uint16_t _opcode) {
        PC = registers[0] + (_opcode & 0x0fff);
    };
    // CXNN rand Vx = rand() & NN
    opcode[22] = [&registers](uint16_t _opcode) {
        registers[(_opcode & 0x0f00)] = (rand() % 256) & (_opcode & 0x00ff);
    };
}


Cpu::~Cpu() {

}
