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
        if(addr_abs & 0xFF00 != pc & 0xFF00)
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

        if(addr_abs & 0xFF00 != pc & 0xFF00)
            cycles++;

        pc = addr_abs;
    }
    return 0;
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