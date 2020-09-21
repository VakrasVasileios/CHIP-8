#include <stdlib.h>
#include "cpu.hpp"

uint16_t
Cpu::PopStack() {
    return stack[sp--];
}

void
Cpu::InsertToStack(uint16_t _address) {
    stack[++sp] = _address;
}

Cpu::Cpu(Memory* _memory, Display* _display) {
    bus = Bus(_memory, _display);

    // 00E0 display clear display
    opcode[0] = [&bus]() {
        bus->ClearDisplay();
    };
    // 00EE flow return
    opcode[1] = [&PC]() {
        *PC = PopStack();
    };
    // 1NNN flow goto NNN
    opcode[2] = [&PC](uint16_t _opcode) {
        InsertToStack(*PC);
        *PC = _opcode & 0x0fff;
    };
    // 2NNN flow *(0x0NNN)()
    opcode[3] = [&PC](uint16_t _opcode) {
        InsertToStack(*PC);
        *PC = _opcode & 0x0fff;
    };
    // 3XNN cond if(Vx == NN)
    opcode[4] = [&PC](uint16_t _opcode) {
        *PC += 4 * ((_opcode & 0x0f00) == (_opcode & 0x00ff));
    };
    // 4XNN cond if(Vx != NN)
    opcode[5] = [&PC](uint16_t _opcode) {
        *PC += 4 * ((_opcode & 0x0f00) != (_opcode & 0x00ff));
    };
    // 5XY0 cond if(Vx == Vy)
    opcode[6] = [&PC](uint16_t _opcode) {
        *PC += 4 * ((_opcode & 0x0f00) == (_opcode & 0x00f0))
    }
    // 6XNN const Vx = NN
    opcode[7] = [&v](uint16_t _opcode) {
        v[(_opcode & 0x0f00)] = _opcode & 0x00ff;
    };
    // 7XNN const Vx += NN
    opcode[8] = [&v](uint16_t _opcode) {
        v[(_opcode & 0x0f00)] += _opcode & 0x0ff;
    };
    // 8XY0 assign Vx = Vy
    opcode[9] = [&v](uint16_t _opcode) {
        v[(_opcode & 0x0f00)] = v[(_opcode & 0x00f0)];
    };
    // 8XY1 bitop Vx = Vx | Vy
    opcode[10] = [&v](uint16_t _opcode) {
        v[(_opcode & 0x0f00)] = v[(_opcode & 0x0f00)] | v[(_opcode & 0x00f0)];
    };
    // 8XY2 bitop Vx = Vx & Vy
    opcode[11] = [&v](uint16_t _opcode) {
        v[(_opcode & 0x0f00)] = v[(_opcode & 0x0f00)] & v[(_opcode & 0x00f0)];
    };
    // 8XY3 bitop Vx = Vx ^ Vy
    opcode[12] = [&v](uint16_t _opcode) {
        v[(_opcode & 0x0f00)] = v[(_opcode & 0x0f00)] ^ v[(_opcode & 0x00f0)];
    };
    // 8XY4 math Vx += Vy
    opcode[13] = [&v](uint16_t _opcode) {
        v[(_opcode & 0x0f00)] += v[(_opcode & 0x00f0)];
    };
    // 8XY5 math Vx -= Vy
    opcode[14] = [&v](uint16_t _opcode) {
        v[(_opcode & 0x0f00)] -= v[(_opcode & 0x00f0)];
    };
    // 8XY6 bitop Vx >>= Vy
    opcode[15] = [&v](uint16_t _opcode) {
        v[15] = v[(_opcode & 0x0f00)] & 1;          // store least significant bit to VF
        v[(_opcode & 0x0f00)] >>= 1;
    };
    // 8XY7  math Vx = Vy - Vx
    opcode[16] = [&v](uint16_t _opcode) {
        v[(_opcode & 0x0f00)] = v[(_opcode & 0x00f0)] - v[(_opcode & 0x0f00)];
    };
    // 8XYE bitop Vx <<= Vy
    opcode[17] = [&v](uint16_t _opcode) {
        v[15] = v[(_opcode & 0x0f00)] & (1 << 7);   // store most significant bit to VF
        v[(_opcode & 0x0f00)] <<= 1;
    };
    // 9XY0 cond if(Vx != Vy)
    opcode[18] = [&PC](uint16_t _opcode) {
        *PC += 4 * ((_opcode & 0x0f00) != (_opcode & 0x00f0));
    };
    // ANNN mem I = NNN
    opcode[19] = [&, v, I](uint16_t _opcode) {
        I = _opcode & 0X0fff
    };
    // BNNN flow PC = V0 + NNN
    opcode[20] = [&, v, PC](uint16_t _opcode) {
        PC = (_opcode & 0x0fff) + v[0];
    };
    // CXNN rand Vx = rand() & NN
    opcode[21] = [&v](uint16_t _opcode) {
        v[(_opcode & 0x0f00)] = (rand() % 256) & (_opcode & 0x00ff);
    };
    // FX1E mem I += Vx
    opcode[29] = [&I](uint16_t _opcode) {
        *I += (_opcode & 0x0f00);
    };
}


Cpu::~Cpu() {

}
