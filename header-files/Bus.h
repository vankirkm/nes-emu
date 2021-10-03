//
// Created by Michael Van Kirk on 7/30/21.
//

#ifndef NESEMULATOR_BUS_H
#define NESEMULATOR_BUS_H

#pragma once
#include <cstdint>
#include "Cpu.h"
#include <array>

class Bus {
public:
    Bus();
    ~Bus();

public:
    Cpu cpu;
    std::array<uint8_t, 64 * 1024> ram;

public:
    void write(uint16_t addr, uint8_t data);
    uint8_t read(uint16_t addr, bool bReadOnly = false);
};

#endif //NESEMULATOR_BUS_H
