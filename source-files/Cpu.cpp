//
// Created by Michael Van Kirk on 7/30/21.
//
#include "../header-files/Cpu.h"
#include "../header-files/Bus.h"

Cpu::Cpu(){

    using cpu = Cpu;
    lookup_table = {

       //--------------------------------X0------------------------------------------X1-----------------------------------------X2----------------------------------------X3-----------------------------------------X4----------------------------------------X5----------------------------------------X6-----------------------------------------X7----------------------------------------X8----------------------------------------X9-----------------------------------------XA----------------------------------------XB-----------------------------------------XC----------------------------------------XD----------------------------------------XE-----------------------------------------XF
       /* 0X */     {"BRK", &cpu::BRK, &cpu::IMP, 7}, {"ORA", &cpu::ORA, &cpu::INX, 6}, {"???", &cpu::XXX, &cpu::IMP, 2}, {"???", &cpu::XXX, &cpu::INX, 2}, {"???", &cpu::XXX, &cpu::ZP0, 2}, {"ORA", &cpu::ORA, &cpu::ZP0, 3}, {"ASL", &cpu::ASL, &cpu::ZP0, 5}, {"???", &cpu::XXX, &cpu::ZP0, 2}, {"PHP", &cpu::PHP, &cpu::IMP, 3}, {"ORA", &cpu::ORA, &cpu::IMM, 2}, {"ASL", &cpu::ASL, &cpu::IMP, 2}, {"???", &cpu::XXX, &cpu::IMM, 2}, {"???", &cpu::XXX, &cpu::ABS, 4}, {"ORA", &cpu::ORA, &cpu::ABS, 4}, {"ASL", &cpu::ASL, &cpu::ABS, 6}, {"???", &cpu::XXX, &cpu::ABS, 6},
       /* 1X */     {"BPL", &cpu::BPL, &cpu::REL, 2}, {"ORA", &cpu::ORA, &cpu::IZY, 5}, {"???", &cpu::XXX, &cpu::IMP, 2}, {"???", &cpu::XXX, &cpu::IZX, 8}, {"???", &cpu::XXX, &cpu::ZPX, 4}, {"ORA", &cpu::ORA, &cpu::ZPX, 4}, {"ASL", &cpu::ASL, &cpu::ZPX, 6}, {"???", &cpu::XXX, &cpu::ZPX, 6}, {"CLC", &cpu::CLC, &cpu::IMP, 2}, {"ORA", &cpu::ORA, &cpu::ABY, 4}, {"???", &cpu::XXX, &cpu::IMP, 2}, {"???", &cpu::XXX, &cpu::ABY, 7}, {"???", &cpu::XXX, &cpu::ABX, 4}, {"ORA", &cpu::ORA, &cpu::ABX, 4}, {"ASL", &cpu::ASL, &cpu::ABX, 7}, {"???", &cpu::XXX, &cpu::ABX, 7},
       /* 2X */     {"JSR", &cpu::JSR, &cpu::ABS, 6}, {"AND", &cpu::AND, &cpu::IZX, 6}, {"???", &cpu::XXX, &cpu::IMP, 2}, {"???", &cpu::XXX, &cpu::IZX, 8}, {"BIT", &cpu::BIT, &cpu::ZP0, 3}, {"AND", &cpu::AND, &cpu::ZP0, 3}, {"ROL", &cpu::ROL, &cpu::ZP0, 5}, {"???", &cpu::XXX, &cpu::ZP0, 5}, {"PLP", &cpu::PLP, &cpu::IMP, 4}, {"AND", &cpu::AND, &cpu::IMM, 2}, {"ROL", &cpu::ROL, &cpu::IMP, 2}, {"???", &cpu::XXX, &cpu::IMM, 2}, {"BIT", &cpu::BIT, &cpu::ABS, 4}, {"AND", &cpu::AND, &cpu::ABS, 4}, {"ROL", &cpu::ROL, &cpu::ABS, 6}, {"???", &cpu::XXX, &cpu::ABS, 6},
       /* 3X */     {"BMI", &cpu::BMI, &cpu::REL, 2}, {"AND", &cpu::AND, &cpu::IZY, 5}, {"???", &cpu::XXX, &cpu::IMP, 2}, {"???", &cpu::XXX, &cpu::IZY, 8}, {"???", &cpu::XXX, &cpu::ZPX, 4}, {"AND", &cpu::AND, &cpu::ZPX, 4}, {"ROL", &cpu::ROL, &cpu::ZPX, 6}, {"???", &cpu::XXX, &cpu::ZPX, 6}, {"SEC", &cpu::SEC, &cpu::IMP, 2}, {"AND", &cpu::AND, &cpu::ABY, 4}, {"???", &cpu::XXX, &cpu::IMP, 2}, {"???", &cpu::XXX, &cpu::ABY, 7}, {"BIT", &cpu::BIT, &cpu::ABX, 4}, {"AND", &cpu::AND, &cpu::ABX, 4}, {"ROL", &cpu::ROL, &cpu::ABX, 7}, {"???", &cpu::XXX, &cpu::ABX, 7},
       /* 4X */     {"RTI", &cpu::RTI, &cpu::IMP, 6}, {"EOR", &cpu::EOR, &cpu::IZX, 6}, {"???", &cpu::XXX, &cpu::IMP, 2}, {"???", &cpu::XXX, &cpu::IZX, 8}, {"???", &cpu::XXX, &cpu::ZP0, 3}, {"EOR", &cpu::EOR, &cpu::ZP0, 3}, {"LSR", &cpu::LSR, &cpu::ZP0, 5}, {"???", &cpu::XXX, &cpu::ZP0, 5}, {"PHA", &cpu::PHA, &cpu::IMP, 3}, {"EOR", &cpu::EOR, &cpu::IMM, 2}, {"LSR", &cpu::LSR, &cpu::IMP, 2}, {"???", &cpu::XXX, &cpu::IMM, 2}, {"JMP", &cpu::JMP, &cpu::ABS, 3}, {"EOR", &cpu::EOR, &cpu::ABS, 4}, {"LSR", &cpu::LSR, &cpu::ABS, 6}, {"???", &cpu::XXX, &cpu::ABS, 6},
       /* 5X */     {"BVC", &cpu::BVC, &cpu::REL, 2}, {"EOR", &cpu::EOR, &cpu::IZY, 5}, {"???", &cpu::XXX, &cpu::IMP, 2}, {"???", &cpu::XXX, &cpu::IZY, 8}, {"???", &cpu::XXX, &cpu::ZPX, 4}, {"EOR", &cpu::EOR, &cpu::ZPX, 4}, {"LSR", &cpu::LSR, &cpu::ZPX, 6}, {"???", &cpu::XXX, &cpu::ZPX, 6}, {"CLI", &cpu::CLI, &cpu::IMP, 2}, {"EOR", &cpu::EOR, &cpu::ABY, 4}, {"???", &cpu::XXX, &cpu::IMP, 2}, {"???", &cpu::XXX, &cpu::ABY, 7}, {"???", &cpu::XXX, &cpu::ABX, 4}, {"EOR", &cpu::EOR, &cpu::ABX, 4}, {"LSR", &cpu::LSR, &cpu::ABX, 7}, {"???", &cpu::XXX, &cpu::ABX, 7},
       /* 6X */     {"RTS", &cpu::RTS, &cpu::IMP, 6}, {"ADC", &cpu::ADC, &cpu::IZX, 6}, {"???", &cpu::XXX, &cpu::IMP, 2}, {"???", &cpu::XXX, &cpu::IZX, 8}, {"???", &cpu::XXX, &cpu::ZP0, 3}, {"ADC", &cpu::ADC, &cpu::ZP0, 3}, {"ROR", &cpu::ROR, &cpu::ZP0, 5}, {"???", &cpu::XXX, &cpu::ZP0, 5}, {"PLA", &cpu::PLA, &cpu::IMP, 4}, {"ADC", &cpu::ADC, &cpu::IMM, 2}, {"ROR", &cpu::ROR, &cpu::IMP, 2}, {"???", &cpu::XXX, &cpu::IMM, 2}, {"JMP", &cpu::JMP, &cpu::IND, 5}, {"ADC", &cpu::ADC, &cpu::ABS, 4}, {"ROR", &cpu::ROR, &cpu::ABS, 6}, {"???", &cpu::XXX, &cpu::ABS, 6},
       /* 7X */     {"BVS", &cpu::BVS, &cpu::REL, 2}, {"ADC", &cpu::ADC, &cpu::IZY, 5}, {"???", &cpu::XXX, &cpu::IMP, 2}, {"???", &cpu::XXX, &cpu::IZY, 8}, {"???", &cpu::XXX, &cpu::ZPX, 4}, {"ADC", &cpu::ADC, &cpu::ZPX, 4}, {"ROR", &cpu::ROR, &cpu::ZPX, 6}, {"???", &cpu::XXX, &cpu::ZPX, 6}, {"SEI", &cpu::SEI, &cpu::IMP, 2}, {"ADC", &cpu::ADC, &cpu::ABY, 4}, {"ROR", &cpu::ROR, &cpu::IMP, 2}, {"???", &cpu::XXX, &cpu::ABY, 7}, {"???", &cpu::XXX, &cpu::ABX, 4}, {"ADC", &cpu::ADC, &cpu::ABX, 4}, {"ROR", &cpu::ROR, &cpu::ABX, 7}, {"???", &cpu::XXX, &cpu::ABX, 7},
       /* 8X */     {"???", &cpu::XXX, &cpu::IMM, 2}, {"STA", &cpu::STA, &cpu::IZX, 6}, {"???", &cpu::XXX, &cpu::IMM, 2}, {"???", &cpu::XXX, &cpu::IZX, 6}, {"STY", &cpu::STY, &cpu::ZP0, 3}, {"STA", &cpu::STA, &cpu::ZP0, 3}, {"STX", &cpu::STX, &cpu::ZP0, 3}, {"???", &cpu::XXX, &cpu::ZP0, 3}, {"DEY", &cpu::DEY, &cpu::IMP, 2}, {"???", &cpu::XXX, &cpu::IMM, 2}, {"TXA", &cpu::TXA, &cpu::IMP, 2}, {"???", &cpu::XXX, &cpu::IMM, 2}, {"STY", &cpu::STY, &cpu::ABS, 4}, {"STA", &cpu::STA, &cpu::ABS, 4}, {"STX", &cpu::STX, &cpu::ABS, 4}, {"???", &cpu::XXX, &cpu::ABS, 4},
       /* 9X */     {"BCC", &cpu::BCC, &cpu::REL, 2}, {"STA", &cpu::STA, &cpu::IZY, 6}, {"???", &cpu::XXX, &cpu::IMP, 2}, {"???", &cpu::XXX, &cpu::IZY, 6}, {"STY", &cpu::STY, &cpu::ZPX, 4}, {"STA", &cpu::STA, &cpu::ZPX, 4}, {"STX", &cpu::STX, &cpu::ZPY, 4}, {"???", &cpu::XXX, &cpu::ZPY, 4}, {"TYA", &cpu::TYA, &cpu::IMP, 2}, {"STA", &cpu::STA, &cpu::ABY, 5}, {"TXS", &cpu::TXS, &cpu::IMP, 2}, {"???", &cpu::XXX, &cpu::ABY, 5}, {"???", &cpu::XXX, &cpu::ABX, 5}, {"STA", &cpu::STA, &cpu::ABX, 5}, {"???", &cpu::XXX, &cpu::ABY, 5}, {"???", &cpu::XXX, &cpu::ABY, 5},
       /* AX */     {"LDY", &cpu::LDY, &cpu::IMM, 2}, {"LDA", &cpu::LDA, &cpu::IZX, 6}, {"LDX", &cpu::LDX, &cpu::IMM, 2}, {"???", &cpu::XXX, &cpu::IZX, 6}, {"LDY", &cpu::LDY, &cpu::ZP0, 3}, {"LDA", &cpu::LDA, &cpu::ZP0, 3}, {"LDX", &cpu::LDX, &cpu::ZP0, 3}, {"???", &cpu::XXX, &cpu::ZP0, 3}, {"TAY", &cpu::TAY, &cpu::IMP, 2}, {"LDA", &cpu::LDA, &cpu::IMM, 2}, {"TAX", &cpu::TAX, &cpu::IMP, 2}, {"???", &cpu::XXX, &cpu::IMM, 2}, {"LDY", &cpu::LDY, &cpu::ABS, 4}, {"LDA", &cpu::LDA, &cpu::ABS, 4}, {"LDX", &cpu::LDX, &cpu::ABS, 4}, {"???", &cpu::XXX, &cpu::ABS, 4},
       /* BX */     {"BCS", &cpu::BCS, &cpu::REL, 2}, {"LDA", &cpu::LDA, &cpu::IZY, 5}, {"???", &cpu::XXX, &cpu::IMP, 2}, {"???", &cpu::XXX, &cpu::IZY, 5}, {"LDY", &cpu::LDY, &cpu::ZPX, 4}, {"LDA", &cpu::LDA, &cpu::ZPX, 4}, {"LDX", &cpu::LDX, &cpu::ZPY, 4}, {"???", &cpu::XXX, &cpu::ZPY, 4}, {"CLV", &cpu::CLV, &cpu::IMP, 2}, {"LDA", &cpu::LDA, &cpu::ABY, 4}, {"TSX", &cpu::TSX, &cpu::IMP, 2}, {"???", &cpu::XXX, &cpu::ABY, 4}, {"LDY", &cpu::LDY, &cpu::ABX, 4}, {"LDA", &cpu::LDA, &cpu::ABX, 4}, {"LDX", &cpu::LDX, &cpu::ABY, 4}, {"???", &cpu::XXX, &cpu::ABY, 4},
       /* CX */     {"CPY", &cpu::CPY, &cpu::IMM, 2}, {"CMP", &cpu::CMP, &cpu::IZX, 6}, {"???", &cpu::XXX, &cpu::IMM, 2}, {"???", &cpu::XXX, &cpu::IZX, 8}, {"CPY", &cpu::CPY, &cpu::ZP0, 3}, {"CMP", &cpu::CMP, &cpu::ZP0, 3}, {"DEC", &cpu::DEC, &cpu::ZP0, 5}, {"???", &cpu::XXX, &cpu::ZP0, 5}, {"INY", &cpu::INY, &cpu::IMP, 2}, {"CMP", &cpu::CMP, &cpu::IMM, 2}, {"DEX", &cpu::DEX, &cpu::IMP, 2}, {"???", &cpu::XXX, &cpu::IMM, 2}, {"CPY", &cpu::CPY, &cpu::ABS, 4}, {"CMP", &cpu::CMP, &cpu::ABS, 4}, {"DEC", &cpu::DEC, &cpu::ABS, 6}, {"???", &cpu::XXX, &cpu::ABS, 6},
       /* DX */     {"BNE", &cpu::BNE, &cpu::REL, 2}, {"CMP", &cpu::CMP, &cpu::IZY, 5}, {"???", &cpu::XXX, &cpu::IMP, 2}, {"???", &cpu::XXX, &cpu::IZY, 8}, {"???", &cpu::XXX, &cpu::ZPX, 4}, {"CMP", &cpu::CMP, &cpu::ZPX, 4}, {"DEC", &cpu::DEC, &cpu::ZPX, 6}, {"???", &cpu::XXX, &cpu::ZPX, 6}, {"CLD", &cpu::CLD, &cpu::IMP, 2}, {"CMP", &cpu::CMP, &cpu::ABY, 4}, {"???", &cpu::XXX, &cpu::IMP, 2}, {"???", &cpu::XXX, &cpu::ABY, 7}, {"???", &cpu::XXX, &cpu::ABX, 4}, {"CMP", &cpu::CMP, &cpu::ABX, 4}, {"DEC", &cpu::DEC, &cpu::ABX, 7}, {"???", &cpu::XXX, &cpu::ABX, 7},
       /* EX */     {"CPX", &cpu::CPX, &cpu::IMM, 2}, {"SBC", &cpu::SBC, &cpu::IZX, 6}, {"???", &cpu::XXX, &cpu::IMM, 2}, {"???", &cpu::XXX, &cpu::IZX, 8}, {"CPX", &cpu::CPX, &cpu::ZP0, 3}, {"SBC", &cpu::SBC, &cpu::ZP0, 3}, {"INC", &cpu::INC, &cpu::ZP0, 5}, {"???", &cpu::XXX, &cpu::ZP0, 5}, {"INX", &cpu::INX, &cpu::IMP, 2}, {"SBC", &cpu::SBC, &cpu::IMM, 2}, {"NOP", &cpu::NOP, &cpu::IMP, 2}, {"???", &cpu::XXX, &cpu::IMM, 2}, {"CPX", &cpu::CPX, &cpu::ABS, 4}, {"SBC", &cpu::SBC, &cpu::ABS, 4}, {"INC", &cpu::INC, &cpu::ABS, 6}, {"???", &cpu::XXX, &cpu::ABS, 6},
       /* FX */     {"BEQ", &cpu::BEQ, &cpu::REL, 2}, {"SBC", &cpu::SBC, &cpu::IZY, 5}, {"???", &cpu::XXX, &cpu::IMP, 2}, {"???", &cpu::XXX, &cpu::IZY, 8}, {"???", &cpu::XXX, &cpu::ZPX, 4}, {"SBC", &cpu::SBC, &cpu::ZPX, 4}, {"INC", &cpu::INC, &cpu::ZPX, 6}, {"???", &cpu::XXX, &cpu::ZPX, 6}, {"SED", &cpu::SED, &cpu::IMP, 2}, {"SBC", &cpu::SBC, &cpu::ABY, 4}, {"???", &cpu::XXX, &cpu::IMP, 2}, {"???", &cpu::XXX, &cpu::ABY, 7}, {"???", &cpu::XXX, &cpu::ABX, 4}, {"SBC", &cpu::SBC, &cpu::ABX, 4}, {"INC", &cpu::INC, &cpu::ABX, 7}, {"???", &cpu::XXX, &cpu::ABX, 7},

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

// interrupt request
void Cpu::irq() {

    if (GetFlag(I) == 0) {
        write(0x0100 + s_point, (pc >> 8) & 0x00FF);
        s_point--;
        write(0x0100 + s_point, pc & 0x00FF);
        s_point--;

        SetFlag(B, 0);
        SetFlag(U, 1);
        SetFlag(I, 1);
        write(0x0100 + s_point, status);
        s_point--;

        addr_abs = 0xFFFE;
        uint16_t lo = read(addr_abs + 0);
        uint16_t hi = read(addr_abs + 1);
        pc = (hi << 8) | lo;

        cycles = 7;
    }

}

// non-masking interrupt
void Cpu::nmi() {

    if (GetFlag(I) == 0) {
        write(0x0100 + s_point, (pc >> 8) & 0x00FF);
        s_point--;
        write(0x0100 + s_point, pc & 0x00FF);
        s_point--;

        SetFlag(B, 0);
        SetFlag(U, 1);
        SetFlag(I, 1);
        write(0x0100 + s_point, status);
        s_point--;

        addr_abs = 0xFFFA;
        uint16_t lo = read(addr_abs + 0);
        uint16_t hi = read(addr_abs + 1);
        pc = (hi << 8) | lo;

        cycles = 8;
    }

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
    s_point = 0xFF;
    status = 0x00 | U;

    // clear helper variables
    addr_rel = 0x0000;
    addr_abs = 0x0000;
    fetched_data = 0x00;

    cycles = 8;
}

// perform a clock cycle of emulation
void Cpu::clock(){

    if(cycles == 0) {

        // set current opcode
        opcode = read(pc);

        // set unused status flag bit to true (1)
        SetFlag(U, true);

        // increment program counter
        pc++;

        // set the amount of cycles that the instruction will take, then
        // we need to add on any additional cycles required by either
        // the addressing mode or operation
        cycles = lookup_table[opcode].cycles;
        uint8_t addCyclesAddr = (this->*lookup_table[opcode].addrmode)();
        uint8_t addCyclesOp = (this->*lookup_table[opcode].operate)();

        cycles += (addCyclesAddr + addCyclesOp);
    }

    clock_count++;
    cycles--;
}

//////////////////////////////////////////////////////////////
// --------------------ADDRESSING MODES-------------------- //
//////////////////////////////////////////////////////////////

// Implied - addressing mode for simple instructions that does not
// target a specific place in memory. For convenience, put the value
// of the accumulator into fetched_data to later do an operation on it.
uint8_t Cpu::IMP(){
    fetched_data = a;
    return 0;
};

// Immediate - the next byte in memory will be used as a value, so
// point the read address to the next byte.
uint8_t Cpu::IMM(){
    addr_abs = pc++;
    return 0;
};

// Zero Page - allows us to absolutely address a location in the first 0xFF
// bytes of the address range, which allows program memory to be saved by only
// specifying one byte instead of two
uint8_t Cpu::ZP0(){
    addr_abs = read(pc);
    pc++;
    addr_abs &= 0x00FF;
    return 0;
};

// Zero Page w/ X offset - the same as zero page addressing, but the value in
// the X register is added to the single byte value supplied by the instruction
uint8_t Cpu::ZPX(){
    addr_abs = (read(pc) + x);
    pc++;
    addr_abs &= 0x00FF;
    return 0;
};

// Zero page w/ Y offset - same as ZPX, but using the Y register instead
uint8_t Cpu::ZPY(){
    addr_abs = (read(pc) + y);
    pc++;
    addr_abs &= 0x00FF;
    return 0;
};

// Relative - Addressing mode using in branching. The address used must be
// within -128 and +127 of the calling branch instruction
uint8_t Cpu::REL(){
    addr_rel = read(pc);
    pc++;

    if(addr_rel & 0x80) {
        addr_rel |= 0xFF00;
    }
    return 0;
};

// Absolute - entire 16-bit address is taken from the current instruction
uint8_t Cpu::ABS(){
    uint16_t low = read(pc);
    pc++;
    uint16_t high = read(pc);
    pc++;
    addr_abs = (high << 8) | low;
    return 0;
};

// Absolute w/ X offset - Same as absolute addressing, but the current value
// stored in the X register is added to the two-byte address given by the instruction.
// If the resulting address is on a different page, an additional clock cycle is required.
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

// Absolute w/ Y offset - functions the same way as ABX, but using the value in the
// Y register instead.
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

// Indirect - the two-byte address given by the instruction is used to fetch
// the actual address we want from memory.
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

// Indirect X - take the one byte address from the instruction and offset with
// the value in the X register. Then read the actual address from the resultant
// address of this operation.
uint8_t Cpu::IZX(){
    uint16_t temp = read(pc);
    pc++;
    uint16_t low = read((uint16_t)(temp + (uint16_t)x) & 0x00FF);
    uint16_t high = read((uint16_t)(temp + (uint16_t)x + 1) & 0x00FF);
    addr_abs = (high << 8) | low;

    return 0;
};

// Indirect Y - The 1 byte address from the instruction is read and used to index an
// address on page 0x00. The actual 2 byte address is then read form this location
// and then is offset by the value in the Y register. An additional clock cycle is
// required if this results in a change in page.
uint8_t Cpu::IZY(){
    uint16_t tmp = read(pc);
    pc++;
    uint16_t low = read(tmp & 0x00FF);
    uint16_t high = read((tmp + 1) & 0x00FF);
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
    fetch();

    temp = (uint16_t)a + (uint16_t)fetched_data + (uint16_t) GetFlag(C);

    // if temp > 255, we know that whatever value it is (positive or negative)
    // is greater than 8 bits, and can set C to 1
    SetFlag(C, temp > 255);

    // positive + positive = negative <----- overflow occurred
    // negative + negative = positive <----- more overflow
    SetFlag(V, temp > 255);

    SetFlag(N, temp & 0x80);

    SetFlag(Z, (temp & 0x00FF) == 0);

    return 0;
}

// AND - logical AND operation. accumulator = a & memory
uint8_t Cpu::AND() {
    fetch();
    a &= fetched_data;
    SetFlag(N, a & 0x80);
    SetFlag(Z, a == 0x00);
    return 0;
}

// ASL - arithmetic shift left
uint8_t Cpu::ASL() {
    fetch();
    temp = (uint16_t) fetched_data << 1;
    SetFlag(N, temp & 0x80);
    SetFlag(Z, (temp & 0x00FF) & 0x00);
    SetFlag(C, (temp & 0xFF00) > 0 );

    // if the addressing mode is implied, we need to put the
    // shifted data into the accumulator. Otherwise, the
    // shifted data gets written to memory
    if(lookup_table[opcode].addrmode == &Cpu::IMP) {
        a = temp & 0x00FF;
    }else {
        write(addr_abs, (temp & 0x00FF));
    }
    return 0;
}

// BCC - Branch if carry flag is clear
uint8_t Cpu::BCC() {

    if(GetFlag(C) == 0) {
        cycles++;
        addr_abs = pc + addr_rel;

        // if the address we are branching to is not on the
        // same page as the previous address, we need to
        // add an additional clock cycle
        if(addr_abs & 0xFF00 != pc & 0xFF00)
            cycles++;

        pc = addr_abs;
    }
    return 0;
}

// BCS - Branch if carry flag is set. Follows the same cycle
// rules as BCC. If the new address is not on the same page as
// the previous address, we must add a clock cycle
uint8_t Cpu::BCS() {

    if(GetFlag(C) != 0) {
        cycles++;
        addr_abs = pc + addr_rel;

        // if the address we are branching to is not on the
        // same page as the previous address, we need to
        // add an additional clock cycle
        if((addr_abs & 0xFF00) != (pc & 0xFF00))
            cycles++;

        pc = addr_abs;
    }
    return 0;
}

// BEQ - Branch if zero flag is set. Follows the same cycle
// rules as BCC. If the new address is not on the same page as
// the previous address, we must add a clock cycle
uint8_t Cpu::BEQ() {

    if(GetFlag(Z) != 0) {
        cycles++;
        addr_abs = pc + addr_rel;

        if(addr_abs & 0xFF00 != pc & 0xFF00)
            cycles++;

        pc = addr_abs;
    }
    return 0;
}

// BIT - Bit test. Test if one more bits are set in a memory location
// by ANDing the accumulator with the data fetched from memory. If the
// result of this operation is zero, set the zero flag. Set the overflow
// flag to bit 6 of the fetched data. Set the negative flag to bit 7
// of the fetched data.
uint8_t Cpu::BIT() {
    fetch();
    temp = a & fetched_data;
    SetFlag(Z, (temp & 0x00FF) == 0x00);
    SetFlag(V, fetched_data & (1 << 6));
    SetFlag(N, fetched_data & (1 << 7));
    return 0;
}

// BMI - branch if negative flag is set. Same clock cycle rules as BCC.
uint8_t Cpu::BMI() {

    if(GetFlag(N) == 1) {
        cycles++;
        addr_abs = pc + addr_rel;

        if(addr_abs & 0xFF00 != pc & 0xFF00)
            cycles++;

        pc = addr_abs;
    }
    return 0;
}

// BNE - branch if the zero flag is clear. Same clock cycle rules as BCC
uint8_t Cpu::BNE() {
    if(GetFlag(Z) == 0) {
        cycles++;
        addr_abs = pc + addr_rel;

        if(addr_abs & 0xFF00 != pc & 0xFF00)
            cycles++;

        pc = addr_abs;
    }
    return 0;
}

// BPL - branch if positive (if the negative flag is not set).
// Same clock cycle rules as BCC
uint8_t Cpu::BPL() {
    if(GetFlag(N) == 0) {
        cycles++;
        addr_abs = pc + addr_rel;

        if((addr_abs & 0xFF00) != (pc & 0xFF00))
            cycles++;

        pc = addr_abs;
    }
    return 0;
}

// BRK - instruction forces the generation of an interrupt request.
// The program counter and processor status are pushed on the stack
// then the IRQ interrupt vector at $FFFE/F is loaded into the PC and
// the break flag in the status set to one.
uint8_t Cpu::BRK() {
    
    pc++;
    SetFlag(I, 1);
    write(0x0100 + s_point, (pc >> 8) & 0x00FF);
    s_point--;
    write(0x0100 + s_point, pc & 0x00FF);
    s_point--;
    SetFlag(B, 1);
    write(0x0100 + s_point, status);
    s_point--;
    SetFlag(B, 0);

    pc = (uint16_t)read(0xFFFE) | ((uint16_t)read(0xFFFF) << 8);
    return 0;
}

// BVC - Branch if overflow flag is clear by adding relative displacement
// to program counter. 1 cycle if branch succeeds, 2 cycles if to a new page
uint8_t Cpu::BVC() {

    if(GetFlag(V) == 0) {
        cycles++;
        addr_abs = pc + addr_rel;

        if ((addr_abs & 0xFF00) != (pc & 0xFF00))
            cycles++;

        pc = addr_abs;
    }

    return 0;

}

// BVS - Branch if overflow flag is set by adding relative displacement
// to program counter. 1 cycle if branch succeeds, 2 cycles if to a new page
uint8_t Cpu::BVS() {

    if(GetFlag(V) == 1) {
        cycles++;
        addr_abs = pc + addr_rel;

        if ((addr_abs & 0xFF00) != (pc & 0xFF00))
            cycles++;

        pc = addr_abs;
    }

    return 0;

}

// CLC - clear carry flag
uint8_t Cpu::CLC() {
    SetFlag(C, 0);
    return 0;
}

// CLD - clear decimal mode flag
uint8_t Cpu::CLD() {
    SetFlag(D, 0);
    return 0;
}

// CLI - clear interrupt disable flag
uint8_t Cpu::CLI() {
    SetFlag(I, 0);
    return 0;
}

// CLV - clear overflow flag
uint8_t Cpu::CLV() {
    SetFlag(V, 0);
    return 0;
}

// CMP - compare the contents of the accumulator with
// an item in memory. Set CZN flags accordingly
// FOR ABS X, ABS Y, AND IND X ADDRESSING, MAY NEED
// TO ADD A CYCLE IF PAGE CROSSED
uint8_t Cpu::CMP() {

    fetch();
    temp = (uint16_t)a - (uint16_t)fetched_data;
    SetFlag(C, a >= fetched_data);
    SetFlag(Z, (temp & 0x00FF) == 0x0000);
    SetFlag(N, temp & 0x0080);

    return 1;

}

// CPX - compare the contents of the X register with
// an item in memory. Set CZN flags accordingly
uint8_t Cpu::CPX() {

    fetch();
    temp = (uint16_t)x - (uint16_t)fetched_data;
    SetFlag(C, x >= fetched_data);
    SetFlag(Z, (temp & 0x00FF) == 0x0000);
    SetFlag(N, temp & 0x0080);

    return 0;
}

// CPY - compare the contents of the Y register with
// an item in memory. Set CZN flags accordingly
uint8_t Cpu::CPY() {

    fetch();
    temp = (uint16_t)y - (uint16_t)fetched_data;
    SetFlag(C, y >= fetched_data);
    SetFlag(Z, (temp & 0x00FF) == 0x0000);
    SetFlag(N, temp & 0x0080);

    return 0;
}

// DEC - decrement the value at a specific location in
// memory. set ZN flags accordingly
uint8_t Cpu::DEC() {

    fetch();
    temp = fetched_data - 1;
    write(addr_abs, temp & 0x00FF);
    SetFlag(Z, (temp & 0x00FF) == 0x0000);
    SetFlag(N, temp & 0x0080);

    return 0;
}

// DEX - decrement the value in X register.
// set ZN flags accordingly
uint8_t Cpu::DEX() {

    x--;
    SetFlag(Z, x == 0x00);
    SetFlag(N, x & 0x80);

    return 0;
}

// DEY - decrement the value in Y register.
// set ZN flags accordingly
uint8_t Cpu::DEY() {

    y--;
    SetFlag(Z, y == 0x00);
    SetFlag(N, y & 0x80);
    return 0;
}

// EOR - Exclusive or the accumulator with the contents
// of a fetched piece of data from memory. set ZN flags
// accordingly.
uint8_t Cpu::EOR() {

    fetch();
    a = a ^ fetched_data;
    SetFlag(Z, a == 0x00);
    SetFlag(N, a & 0x80);

    return 1;
}

// INC - increment the value at a specific location in
// memory. set ZN flags accordingly
uint8_t Cpu::INC() {

    fetch();
    temp = fetched_data + 1;
    write(addr_abs, temp & 0x00FF);
    SetFlag(Z, (temp & 0x00FF) == 0x0000);
    SetFlag(N, temp & 0x0080);

    return 0;
}

// INX - increment the X register. Set ZN flags accordingly
uint8_t Cpu::INX() {

    x++;
    SetFlag(Z, x == 0x00);
    SetFlag(N, x & 0x80);

    return 0;
}

// INY - increment the Y register. Set ZN flags accordingly
uint8_t Cpu::INY() {

    y++;
    SetFlag(Z, y == 0x00);
    SetFlag(N, y & 0x80);

    return 0;
}

// JMP - sets the program counter to the address specified
// by the operand
uint8_t Cpu::JMP() {

    pc = addr_abs;

    return 0;
}


// JSR - jump to subroutine. pushes the address (minus one) of the
// return point on to the stack and then sets the program counter
// to the target memory address.
uint8_t Cpu::JSR() {

    pc--;

    write(0x0100 + s_point, (pc >> 8) & 0x00FF);
    s_point--;
    write(0x0100 + s_point, pc & 0x00FF);
    s_point--;

    pc = addr_abs;

    return 0;
}

// LDA - Loads a byte of memory into the accumulator
// setting the zero and negative flags as appropriate.
uint8_t Cpu::LDA() {

    fetch();
    a = fetched_data;
    SetFlag(Z, a == 0);
    SetFlag(N, a & 0x80);

    return 1;
}

// LDX - Loads a byte of memory into the X register
// setting the zero and negative flags as appropriate.
uint8_t Cpu::LDX() {

    fetch();
    x = fetched_data;
    SetFlag(Z, x == 0);
    SetFlag(N, x & 0x80);

    return 1;
}

// LDY - Loads a byte of memory into the Y register
// setting the zero and negative flags as appropriate.
uint8_t Cpu::LDY() {

    fetch();
    y = fetched_data;
    SetFlag(Z, y == 0);
    SetFlag(N, y & 0x80);

    return 0;
}

// LSR - Each of the bits in A or M is shifted one place to the right.
// The bit that was in bit 0 is shifted into the carry flag.
// Bit 7 is set to zero.
uint8_t Cpu::LSR() {

    fetch();
    // If addressing mode is implied, we are working with the accumulator.
    // Otherwise, we are working with data from memory
    if (lookup_table[opcode].addrmode == &Cpu::IMP){
        SetFlag(C, a & 0x0001);
        temp = a >> 1;
        a = temp & 0x00FF;
    }else {
        SetFlag(C, fetched_data & 0x0001);
        temp = fetched_data >> 1;
        write(addr_abs, temp & 0x00FF);
    }

    SetFlag(Z, (temp & 0x00FF) == 0x0000);
    SetFlag(N, temp & 0x0080);

    return 0;
}

uint8_t Cpu::NOP() {
    return 0;
}

// ORA - An inclusive OR is performed, bit by bit, on the
// accumulator contents using the contents of a byte of memory.
uint8_t Cpu::ORA() {
    fetch();

    a = a | fetched_data;
    SetFlag(Z, a == 0x00);
    SetFlag(N, a & 0x80);

    return 1;
}

// PHA - Pushes a copy of the accumulator on to the stack.
uint8_t Cpu::PHA() {

    write(0x0100 + s_point, a);
    s_point--;

    return 0;
}

// PHP - Pushes a copy of the status flags on to the stack.
uint8_t Cpu::PHP() {

    write(0x0100 + s_point, status);
    s_point--;
    return 0;

}

// PLA - pulls an 8 bit value off the stack into the accumulator
// Z and N flags are set appropriately
uint8_t Cpu::PLA() {

    s_point++;
    a = read(0x100 + s_point);
    SetFlag(Z, a == 0x00);
    SetFlag(N, a & 0x80);
    return 0;
}

// PLP - pulls an 8 bit value off the stack into the status register
// Z and N flags are set appropriately
uint8_t Cpu::PLP() {

    s_point++;
    status = read(0x100 + s_point);
    SetFlag(U, 1);

    return 0;
}

// ROL - Move each of the bits in either A or M one place to the left.
// Bit 0 is filled with the current value of the carry flag whilst
// the old bit 7 becomes the new carry flag value.
uint8_t Cpu::ROL() {

    fetch();

    if (lookup_table[opcode].addrmode == &Cpu::IMP) {
        temp = (uint16_t)(a << 1) | GetFlag(C);
        a = temp & 0x00FF;
    }

    else {
        temp = (uint16_t)(fetched_data << 1) | GetFlag(C);
        write(addr_abs, temp & 0x00FF);
    }

    SetFlag(C, temp & 0xFF00);
    SetFlag(Z, (temp & 0x00FF) == 0x0000);
    SetFlag(N, temp & 0x0080);

    return 0;
}

uint8_t Cpu::ROR() {

    fetch();

    if (lookup_table[opcode].addrmode == &Cpu::IMP) {
        temp = (uint16_t)(a >> 1) | (GetFlag(C) << 7);
        SetFlag(C, a & 0x01);
        a = temp & 0x00FF;
    }

    else {
        temp = (uint16_t)(fetched_data >> 1) | (GetFlag(C) << 7);
        SetFlag(C, fetched_data & 0x01);
        write(addr_abs, temp & 0x00FF);
    }

    SetFlag(Z, (temp & 0x00FF) == 0x0000);
    SetFlag(N, temp & 0x0080);

    return 0;
}

uint8_t Cpu::RTI() {

    s_point++;
    status = read(0x0100 + s_point);

    s_point++;
    pc = (uint16_t)read(0x0100 + s_point);
    s_point++;
    pc |= (uint16_t)read(0x0100 + s_point) << 8;

    return 0;
}

uint8_t Cpu::RTS() {

    s_point++;
    pc = (uint16_t)read(0x0100 + s_point);
    s_point++;
    pc |= (uint16_t)read(0x0100 + s_point) << 8;

    pc++;

    return 0;
}



uint8_t Cpu::SBC() {

    fetch();

    // We can invert the bottom 8 bits with bitwise xor
    uint16_t value = ((uint16_t)fetched_data) ^ 0x00FF;

    // then perform the same operation as addition
    temp = (uint16_t)a + value + (uint16_t)GetFlag(C);
    SetFlag(C, temp & 0xFF00);
    SetFlag(Z, ((temp & 0x00FF) == 0));
    SetFlag(V, (temp ^ (uint16_t)a) & (temp ^ value) & 0x0080);
    SetFlag(N, temp & 0x0080);
    a = temp & 0x00FF;

    return 1;

}


// SEC - set carry flag
uint8_t Cpu::SEC() {

    SetFlag(C, 1);

    return 0;
}

// SED - set decimal mode flag
uint8_t Cpu::SED() {

    SetFlag(D, 1);

    return 0;
}

// SEI - set interrupt disable flag
uint8_t Cpu::SEI() {

    SetFlag(I, 1);

    return 0;
}

// STA - store the contents of the accumulator
// in memory
uint8_t Cpu::STA() {

    write(addr_abs, a);

    return 0;
}

// STA - store the contents of the X register
// in memory
uint8_t Cpu::STX() {

    write(addr_abs, x);

    return 0;
}

// STA - store the contents of the Y register
// in memory
uint8_t Cpu::STY() {

    write(addr_abs, y);

    return 0;
}

// TAX - Copies the current contents of the accumulator into
// the X register and sets the zero and negative flags as appropriate.
uint8_t Cpu::TAX() {

    x = a;
    SetFlag(Z, x == 0x00);
    SetFlag(N, x & 0x80);

    return 0;
}

// TAY - Copies the current contents of the accumulator into
// the Y register and sets the zero and negative flags as appropriate.
uint8_t Cpu::TAY() {

    y = a;
    SetFlag(Z, y == 0x00);
    SetFlag(N, y & 0x80);

    return 0;
}

// TSX - Copies the current contents of the stack register into
// the X register and sets the zero and negative flags as appropriate.
uint8_t Cpu::TSX() {

    x = s_point;
    SetFlag(Z, x == 0x00);
    SetFlag(N, x & 0x80);

    return 0;
}

// TXA - Copies the current contents of the X register into the
// accumulator and sets the zero and negative flags as appropriate.
uint8_t Cpu::TXA() {

    a = x;
    SetFlag(Z, a == 0x00);
    SetFlag(N, a & 0x80);
    return 0;
}

uint8_t Cpu::TXS() {

    s_point = x;

    return 0;
}

// TYA - Copies the current contents of the Y register into the
// accumulator and sets the zero and negative flags as appropriate.
uint8_t Cpu::TYA() {

    a = y;
    SetFlag(Z, a == 0x00);
    SetFlag(N, a & 0x80);

    return 0;
}

uint8_t Cpu::XXX() {
    return 0;
}