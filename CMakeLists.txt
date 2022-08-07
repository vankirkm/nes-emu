cmake_minimum_required(VERSION 3.20)
project(NesEmulator)

set(CMAKE_CXX_STANDARD 14)

set(SDL2_INCLUDE_DIR "/Library/Frameworks/SDL2.framework")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(NesEmulator source-files/main.cpp source-files/Cpu.cpp source-files/Bus.cpp header-files/Cpu.h header-files/Bus.h)
target_link_libraries(NesEmulator ${SDL2_LIBRARIES})
