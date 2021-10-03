cmake_minimum_required(VERSION 3.20)
project(NesEmulator)

set(CMAKE_CXX_STANDARD 14)

add_executable(NesEmulator source-files/main.cpp source-files/Cpu.cpp source-files/Bus.cpp header-files/Cpu.h header-files/Bus.h)
