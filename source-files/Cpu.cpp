//
// Created by Michael Van Kirk on 7/30/21.
//
#include "../header-files/Cpu.h"
#include "../header-files/Bus.h"

Cpu::Cpu(){

    using c = Cpu;
    lookup_table = {

       //--------------------------------X0------------------------------------------X1-----------------------------------------X2----------------------------------------X3-----------------------------------------X4----------------------------------------X5----------------------------------------X6-----------------------------------------X7----------------------------------------X8----------------------------------------X9-----------------------------------------XA----------------------------------------XB-----------------------------------------XC----------------------------------------XD----------------------------------------XE-----------------------------------------XF
       /* 0X */     {"BRK", &c::BRK, &c::IMP, 7}, {"ORA", &c::ORA, &c::INX, 6}, {"???", &c::XXX, &c::IMP, 2}, {"???", &c::XXX, &c::INX, 2}, {"???", &c::XXX, &c::ZP0, 2}, {"ORA", &c::ORA, &c::ZP0, 3}, {"ASL", &c::ASL, &c::ZP0, 5}, {"???", &c::XXX, &c::ZP0, 2}, {"PHP", &c::PHP, &c::IMP, 3}, {"ORA", &c::ORA, &c::IMM, 2}, {"ASL", &c::ASL, &c::IMP, 2}, {"???", &c::XXX, &c::IMM, 2}, {"???", &c::XXX, &c::ABS, 4}, {"ORA", &c::ORA, &c::ABS, 4}, {"ASL", &c::ASL, &c::ABS, 6}, {"???", &c::XXX, &c::ABS, 6},
       /* 1X */     {"BPL", &c::BPL, &c::REL, 2}, {"ORA", &c::ORA, &c::IZY, 5}, {"???", &c::XXX, &c::IMP, 2}, {"???", &c::XXX, &c::IZX, 8}, {"???", &c::XXX, &c::ZPX, 4}, {"ORA", &c::ORA, &c::ZPX, 4}, {"ASL", &c::ASL, &c::ZPX, 6}, {"???", &c::XXX, &c::ZPX, 6}, {"CLC", &c::CLC, &c::IMP, 2}, {"ORA", &c::ORA, &c::ABY, 4}, {"???", &c::XXX, &c::IMP, 2}, {"???", &c::XXX, &c::ABY, 7}, {"???", &c::XXX, &c::ABX, 4}, {"ORA", &c::ORA, &c::ABX, 4}, {"ASL", &c::ASL, &c::ABX, 7}, {"???", &c::XXX, &c::ABX, 7},
       /* 2X */     {"JSR", &c::JSR, &c::ABS, 6}, {"AND", &c::AND, &c::IZX, 6}, {"???", &c::XXX, &c::IMP, 2}, {"???", &c::XXX, &c::IZX, 8}, {"BIT", &c::BIT, &c::ZP0, 3}, {"AND", &c::AND, &c::ZP0, 3}, {"ROL", &c::ROL, &c::ZP0, 5}, {"???", &c::XXX, &c::ZP0, 5}, {"PLP", &c::PLP, &c::IMP, 4}, {"AND", &c::AND, &c::IMM, 2}, {"ROL", &c::ROL, &c::IMP, 2}, {"???", &c::XXX, &c::IMM, 2}, {"BIT", &c::BIT, &c::ABS, 4}, {"AND", &c::AND, &c::ABS, 4}, {"ROL", &c::ROL, &c::ABS, 6}, {"???", &c::XXX, &c::ABS, 6},
       /* 3X */     {"BMI", &c::BMI, &c::REL, 2}, {"AND", &c::AND, &c::IZY, 5}, {"???", &c::XXX, &c::IMP, 2}, {"???", &c::XXX, &c::IZY, 8}, {"???", &c::XXX, &c::ZPX, 4}, {"AND", &c::AND, &c::ZPX, 4}, {"ROL", &c::ROL, &c::ZPX, 6}, {"???", &c::XXX, &c::ZPX, 6}, {"SEC", &c::SEC, &c::IMP, 2}, {"AND", &c::AND, &c::ABY, 4}, {"???", &c::XXX, &c::IMP, 2}, {"???", &c::XXX, &c::ABY, 7}, {"BIT", &c::BIT, &c::ABX, 4}, {"AND", &c::AND, &c::ABX, 4}, {"ROL", &c::ROL, &c::ABX, 7}, {"???", &c::XXX, &c::ABX, 7},
       /* 4X */     {"RTI", &c::RTI, &c::IMP, 6}, {"EOR", &c::EOR, &c::IZX, 6}, {"???", &c::XXX, &c::IMP, 2}, {"???", &c::XXX, &c::IZX, 8}, {"???", &c::XXX, &c::ZP0, 3}, {"EOR", &c::EOR, &c::ZP0, 3}, {"LSR", &c::LSR, &c::ZP0, 5}, {"???", &c::XXX, &c::ZP0, 5}, {"PHA", &c::PHA, &c::IMP, 3}, {"EOR", &c::EOR, &c::IMM, 2}, {"LSR", &c::LSR, &c::IMP, 2}, {"???", &c::XXX, &c::IMM, 2}, {"JMP", &c::JMP, &c::ABS, 3}, {"EOR", &c::EOR, &c::ABS, 4}, {"LSR", &c::LSR, &c::ABS, 6}, {"???", &c::XXX, &c::ABS, 6},
       /* 5X */     {"BVC", &c::BVC, &c::REL, 2}, {"EOR", &c::EOR, &c::IZY, 5}, {"???", &c::XXX, &c::IMP, 2}, {"???", &c::XXX, &c::IZY, 8}, {"???", &c::XXX, &c::ZPX, 4}, {"EOR", &c::EOR, &c::ZPX, 4}, {"LSR", &c::LSR, &c::ZPX, 6}, {"???", &c::XXX, &c::ZPX, 6}, {"CLI", &c::CLI, &c::IMP, 2}, {"EOR", &c::EOR, &c::ABY, 4}, {"???", &c::XXX, &c::IMP, 2}, {"???", &c::XXX, &c::ABY, 7}, {"???", &c::XXX, &c::ABX, 4}, {"EOR", &c::EOR, &c::ABX, 4}, {"LSR", &c::LSR, &c::ABX, 7}, {"???", &c::XXX, &c::ABX, 7},
       /* 6X */     {"RTS", &c::RTS, &c::IMP, 6}, {"ADC", &c::ADC, &c::IZX, 6}, {"???", &c::XXX, &c::IMP, 2}, {"???", &c::XXX, &c::IZX, 8}, {"???", &c::XXX, &c::ZP0, 3}, {"ADC", &c::ADC, &c::ZP0, 3}, {"ROR", &c::ROR, &c::ZP0, 5}, {"???", &c::XXX, &c::ZP0, 5}, {"PLA", &c::PLA, &c::IMP, 4}, {"ADC", &c::ADC, &c::IMM, 2}, {"ROR", &c::ROR, &c::IMP, 2}, {"???", &c::XXX, &c::IMM, 2}, {"JMP", &c::JMP, &c::IND, 5}, {"ADC", &c::ADC, &c::ABS, 4}, {"ROR", &c::ROR, &c::ABS, 6}, {"???", &c::XXX, &c::ABS, 6},
       /* 7X */     {"BVS", &c::BVS, &c::REL, 2}, {"ADC", &c::ADC, &c::IZY, 5}, {"???", &c::XXX, &c::IMP, 2}, {"???", &c::XXX, &c::IZY, 8}, {"???", &c::XXX, &c::ZPX, 4}, {"ADC", &c::ADC, &c::ZPX, 4}, {"ROR", &c::ROR, &c::ZPX, 6}, {"???", &c::XXX, &c::ZPX, 6}, {"SEI", &c::SEI, &c::IMP, 2}, {"ADC", &c::ADC, &c::ABY, 4}, {"ROR", &c::ROR, &c::IMP, 2}, {"???", &c::XXX, &c::ABY, 7}, {"???", &c::XXX, &c::ABX, 4}, {"ADC", &c::ADC, &c::ABX, 4}, {"ROR", &c::ROR, &c::ABX, 7}, {"???", &c::XXX, &c::ABX, 7},
       /* 8X */     {"???", &c::XXX, &c::IMM, 2}, {"STA", &c::STA, &c::IZX, 6}, {"???", &c::XXX, &c::IMM, 2}, {"???", &c::XXX, &c::IZX, 6}, {"STY", &c::STY, &c::ZP0, 3}, {"STA", &c::STA, &c::ZP0, 3}, {"STX", &c::STX, &c::ZP0, 3}, {"???", &c::XXX, &c::ZP0, 3}, {"DEY", &c::DEY, &c::IMP, 2}, {"???", &c::XXX, &c::IMM, 2}, {"TXA", &c::TXA, &c::IMP, 2}, {"???", &c::XXX, &c::IMM, 2}, {"STY", &c::STY, &c::ABS, 4}, {"STA", &c::STA, &c::ABS, 4}, {"STX", &c::STX, &c::ABS, 4}, {"???", &c::XXX, &c::ABS, 4},
       /* 9X */     {"BCC", &c::BCC, &c::REL, 2}, {"STA", &c::STA, &c::IZY, 6}, {"???", &c::XXX, &c::IMP, 2}, {"???", &c::XXX, &c::IZY, 6}, {"STY", &c::STY, &c::ZPX, 4}, {"STA", &c::STA, &c::ZPX, 4}, {"STX", &c::STX, &c::ZPY, 4}, {"???", &c::XXX, &c::ZPY, 4}, {"TYA", &c::TYA, &c::IMP, 2}, {"STA", &c::STA, &c::ABY, 5}, {"TXS", &c::TXS, &c::IMP, 2}, {"???", &c::XXX, &c::ABY, 5}, {"???", &c::XXX, &c::ABX, 5}, {"STA", &c::STA, &c::ABX, 5}, {"???", &c::XXX, &c::ABY, 5}, {"???", &c::XXX, &c::ABY, 5},
       /* AX */     {"LDY", &c::LDY, &c::IMM, 2}, {"LDA", &c::LDA, &c::IZX, 6}, {"LDX", &c::LDX, &c::IMM, 2}, {"???", &c::XXX, &c::IZX, 6}, {"LDY", &c::LDY, &c::ZP0, 3}, {"LDA", &c::LDA, &c::ZP0, 3}, {"LDX", &c::LDX, &c::ZP0, 3}, {"???", &c::XXX, &c::ZP0, 3}, {"TAY", &c::TAY, &c::IMP, 2}, {"LDA", &c::LDA, &c::IMM, 2}, {"TAX", &c::TAX, &c::IMP, 2}, {"???", &c::XXX, &c::IMM, 2}, {"LDY", &c::LDY, &c::ABS, 4}, {"LDA", &c::LDA, &c::ABS, 4}, {"LDX", &c::LDX, &c::ABS, 4}, {"???", &c::XXX, &c::ABS, 4},
       /* BX */     {"BCS", &c::BCS, &c::REL, 2}, {"LDA", &c::LDA, &c::IZY, 5}, {"???", &c::XXX, &c::IMP, 2}, {"???", &c::XXX, &c::IZY, 5}, {"LDY", &c::LDY, &c::ZPX, 4}, {"LDA", &c::LDA, &c::ZPX, 4}, {"LDX", &c::LDX, &c::ZPY, 4}, {"???", &c::XXX, &c::ZPY, 4}, {"CLV", &c::CLV, &c::IMP, 2}, {"LDA", &c::LDA, &c::ABY, 4}, {"TSX", &c::TSX, &c::IMP, 2}, {"???", &c::XXX, &c::ABY, 4}, {"LDY", &c::LDY, &c::ABX, 4}, {"LDA", &c::LDA, &c::ABX, 4}, {"LDX", &c::LDX, &c::ABY, 4}, {"???", &c::XXX, &c::ABY, 4},
       /* CX */     {"CPY", &c::CPY, &c::IMM, 2}, {"CMP", &c::CMP, &c::IZX, 6}, {"???", &c::XXX, &c::IMM, 2}, {"???", &c::XXX, &c::IZX, 8}, {"CPY", &c::CPY, &c::ZP0, 3}, {"CMP", &c::CMP, &c::ZP0, 3}, {"DEC", &c::DEC, &c::ZP0, 5}, {"???", &c::XXX, &c::ZP0, 5}, {"INY", &c::INY, &c::IMP, 2}, {"CMP", &c::CMP, &c::IMM, 2}, {"DEX", &c::DEX, &c::IMP, 2}, {"???", &c::XXX, &c::IMM, 2}, {"CPY", &c::CPY, &c::ABS, 4}, {"CMP", &c::CMP, &c::ABS, 4}, {"DEC", &c::DEC, &c::ABS, 6}, {"???", &c::XXX, &c::ABS, 6},
       /* DX */     {"BNE", &c::BNE, &c::REL, 2}, {"CMP", &c::CMP, &c::IZY, 5}, {"???", &c::XXX, &c::IMP, 2}, {"???", &c::XXX, &c::IZY, 8}, {"???", &c::XXX, &c::ZPX, 4}, {"CMP", &c::CMP, &c::ZPX, 4}, {"DEC", &c::DEC, &c::ZPX, 6}, {"???", &c::XXX, &c::ZPX, 6}, {"CLD", &c::CLD, &c::IMP, 2}, {"CMP", &c::CMP, &c::ABY, 4}, {"???", &c::XXX, &c::IMP, 2}, {"???", &c::XXX, &c::ABY, 7}, {"???", &c::XXX, &c::ABX, 4}, {"CMP", &c::CMP, &c::ABX, 4}, {"DEC", &c::DEC, &c::ABX, 7}, {"???", &c::XXX, &c::ABX, 7},
       /* EX */     {"CPX", &c::CPX, &c::IMM, 2}, {"SBC", &c::SBC, &c::IZX, 6}, {"???", &c::XXX, &c::IMM, 2}, {"???", &c::XXX, &c::IZX, 8}, {"CPX", &c::CPX, &c::ZP0, 3}, {"SBC", &c::SBC, &c::ZP0, 3}, {"INC", &c::INC, &c::ZP0, 5}, {"???", &c::XXX, &c::ZP0, 5}, {"INX", &c::INX, &c::IMP, 2}, {"SBC", &c::SBC, &c::IMM, 2}, {"NOP", &c::NOP, &c::IMP, 2}, {"???", &c::XXX, &c::IMM, 2}, {"CPX", &c::CPX, &c::ABS, 4}, {"SBC", &c::SBC, &c::ABS, 4}, {"INC", &c::INC, &c::ABS, 6}, {"???", &c::XXX, &c::ABS, 6},
       /* FX */     {"BEQ", &c::BEQ, &c::REL, 2}, {"SBC", &c::SBC, &c::IZY, 5}, {"???", &c::XXX, &c::IMP, 2}, {"???", &c::XXX, &c::IZY, 8}, {"???", &c::XXX, &c::ZPX, 4}, {"SBC", &c::SBC, &c::ZPX, 4}, {"INC", &c::INC, &c::ZPX, 6}, {"???", &c::XXX, &c::ZPX, 6}, {"SED", &c::SED, &c::IMP, 2}, {"SBC", &c::SBC, &c::ABY, 4}, {"???", &c::XXX, &c::IMP, 2}, {"???", &c::XXX, &c::ABY, 7}, {"???", &c::XXX, &c::ABX, 4}, {"SBC", &c::SBC, &c::ABX, 4}, {"INC", &c::INC, &c::ABX, 7}, {"???", &c::XXX, &c::ABX, 7},

    };
}

// destructor
Cpu::~Cpu(){}

uint8_t Cpu::read(uint16_t a){
    return bus->read(a, false);
}

void Cpu::write(uint16_t a, uint8_t d){
    bus->write(a, d);
}

uint8_t Cpu::GetFlag(CPU_FLAGS f){
    return ((status & f) > 0) ? 1 : 0;
}

void Cpu::SetFlag(CPU_FLAGS f, bool v) {
    if(v){
        status |= f;
    }else {
        // We AND the value of the status register with the complement of f to clear
        // just that specific bit from the status register.
        status &= ~f;
    }
}

//////////////////////////////////////////////////////////////
// ---------------------EXTERNAL INPUT--------------------- //
//////////////////////////////////////////////////////////////

void Cpu::reset(){
    // Get address to set program counter to
    addr_abs = 0xFFFC;
    uint16_t lo = read(addr_abs + 0);
    uint16_t hi = read(addr_abs + 1);

    // Set it
    pc = (hi << 8) | lo;

    // Reset internal registers
    a = 0;
    x = 0;
    y = 0;
    s_point = 0xFD;
    status = 0x00 | U;

    // clear helper variables
    addr_rel = 0x0000;
    addr_abs = 0x0000;
    fetched_data = 0x00;

    cycles = 8;
}

// perform a clock cycle of emulation
void Cpu::clock(){
}

//////////////////////////////////////////////////////////////
// --------------------ADDRESSING MODES-------------------- //
//////////////////////////////////////////////////////////////

uint8_t Cpu::IMP(){
    fetched_data = a;
    return 0;
};

uint8_t Cpu::IMM(){
    addr_abs = pc++;
    return 0;
};

uint8_t Cpu::ZP0(){
    addr_abs = read(pc);
    pc++;
    addr_abs &= 0x00FF;
    return 0;
};

uint8_t Cpu::ZPX(){
    addr_abs = (read(pc) + x);
    pc++;
    addr_abs &= 0x00FF;
    return 0;
};

uint8_t Cpu::ZPY(){
    addr_abs = (read(pc) + y);
    pc++;
    return 0;
};

uint8_t Cpu::REL(){
    addr_rel = read(pc);
    pc++;

    if(addr_rel & 0x80) {
        addr_rel |= 0xFF00;
    }
    return 0;
};

uint8_t Cpu::ABS(){
    uint16_t low = read(pc);
    pc++;
    uint16_t high = read(pc);
    pc++;
    addr_abs = (high << 8) | low;
    return 0;
};

uint8_t Cpu::ABX(){
    uint16_t low = read(pc);
    pc++;
    uint16_t high = read(pc);
    pc++;
    addr_abs = (high << 8) | low;
    addr_abs += x;

    if((addr_abs & 0xFF00) != high << 8){
        return 1;
    }
    return 0;
};

uint8_t Cpu::ABY(){
    uint16_t low = read(pc);
    pc++;
    uint16_t high = read(pc);
    pc++;
    addr_abs = (high << 8) | low;
    addr_abs += y;

    if((addr_abs & 0xFF00) != high << 8){
        return 1;
    }
    return 0;
};

// If the 16-bit argument of an indirect JMP is located between 2 pages,
// then the LSB will be read from 0x01FF and the MSB will be read from 0x0100,
// which is a hardware bug in the NES that will yield an invalid address.
uint8_t Cpu::IND(){
    uint16_t pt_low = read(pc);
    pc++;
    uint16_t pt_high = read(pc);
    pc++;

    uint16_t pt = (pt_high << 8) | pt_low;

    if (pt_low == 0x00FF){
        addr_abs = (read(pt & 0xFF00) << 8) | read(pt + 0);
    }else {
        addr_abs = (read(pt + 1) << 8) | read(pt + 0);
    }
    return 0;
};

uint8_t Cpu::IZX(){
    uint16_t temp = read(pc);
    pc++;
    uint16_t low = read((uint16_t)(temp + (uint16_t)x) & 0x00FF);
    uint16_t high = read((uint16_t)(temp + (uint16_t)x + 1) & 0x00FF);
    addr_abs = (high << 8) | low;

    return 0;
};

uint8_t Cpu::IZY(){
    uint16_t temp = read(pc);
    pc++;
    uint16_t low = read(temp & 0x00FF);
    uint16_t high = read((temp + 1) & 0x00FF);
    addr_abs = addr_abs = (high << 8) | low;
    addr_abs += y;

    if((addr_abs & 0xFF00) != (high << 8)){
        return 1;
    }else {
        return 0;
    }
};

uint8_t Cpu::fetch()
{
    if (lookup_table[opcode].addrmode != &Cpu::IMP)
        fetched_data = read(addr_abs);
    return fetched_data;
}

/////////////////////////////////////////////////////
// --------------------OPCODES-------------------- //
/////////////////////////////////////////////////////

uint8_t Cpu::ADC() {
    return 0;
}

uint8_t Cpu::AND() {
    fetch();
    return 0;
}

uint8_t Cpu::ASL() {
    return 0;
}

uint8_t Cpu::BCC() {
    return 0;
}

uint8_t Cpu::BCS() {
    return 0;
}

uint8_t Cpu::BEQ() {
    return 0;
}

uint8_t Cpu::BIT() {
    return 0;
}

uint8_t Cpu::BMI() {
    return 0;
}

uint8_t Cpu::BNE() {
    return 0;
}

uint8_t Cpu::BPL() {
    return 0;
}

uint8_t Cpu::BRK() {
    return 0;
}

uint8_t Cpu::BVC() {
    return 0;
}

uint8_t Cpu::BVS() {
    return 0;
}

uint8_t Cpu::CLC() {
    return 0;
}

uint8_t Cpu::CLD() {
    return 0;
}

uint8_t Cpu::CLI() {
    return 0;
}

uint8_t Cpu::CLV() {
    return 0;
}

uint8_t Cpu::CMP() {
    return 0;
}

uint8_t Cpu::CPX() {
    return 0;
}

uint8_t Cpu::CPY() {
    return 0;
}

uint8_t Cpu::DEC() {
    return 0;
}

uint8_t Cpu::DEX() {
    return 0;
}

uint8_t Cpu::DEY() {
    return 0;
}

uint8_t Cpu::EOR() {
    return 0;
}

uint8_t Cpu::INC() {
    return 0;
}

uint8_t Cpu::INX() {
    return 0;
}

uint8_t Cpu::INY() {
    return 0;
}

uint8_t Cpu::JMP() {
    return 0;
}

uint8_t Cpu::JSR() {
    return 0;
}

uint8_t Cpu::LDA() {
    return 0;
}

uint8_t Cpu::LDX() {
    return 0;
}

uint8_t Cpu::LDY() {
    return 0;
}

uint8_t Cpu::LSR() {
    return 0;
}

uint8_t Cpu::NOP() {
    return 0;
}

uint8_t Cpu::ORA() {
    return 0;
}

uint8_t Cpu::PHA() {
    return 0;
}

uint8_t Cpu::PHP() {
    return 0;
}

uint8_t Cpu::PLA() {
    return 0;
}

uint8_t Cpu::PLP() {
    return 0;
}

uint8_t Cpu::ROL() {
    return 0;
}

uint8_t Cpu::ROR() {
    return 0;
}

uint8_t Cpu::RTI() {
    return 0;
}

uint8_t Cpu::RTS() {
    return 0;
}

uint8_t Cpu::SBC() {
    return 0;
}

uint8_t Cpu::SEC() {
    return 0;
}

uint8_t Cpu::SED() {
    return 0;
}

uint8_t Cpu::SEI() {
    return 0;
}

uint8_t Cpu::STA() {
    return 0;
}

uint8_t Cpu::STX() {
    return 0;
}

uint8_t Cpu::STY() {
    return 0;
}

uint8_t Cpu::TAX() {
    return 0;
}

uint8_t Cpu::TAY() {
    return 0;
}

uint8_t Cpu::TSX() {
    return 0;
}

uint8_t Cpu::TXA() {
    return 0;
}

uint8_t Cpu::TXS() {
    return 0;
}

uint8_t Cpu::TYA() {
    return 0;
}

uint8_t Cpu::XXX() {
    return 0;
}