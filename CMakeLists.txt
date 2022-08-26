cmake_minimum_required(VERSION 3.20)
project(NesEmulator)

set(CMAKE_CXX_STANDARD 14)

# Add SDL2 CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

add_executable(NesEmulator source-files/main.cpp source-files/Cpu.cpp source-files/Bus.cpp header-files/Cpu.h header-files/Bus.h)

# Add all headers files under the include directory
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Add SDL2 library
find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::Main)
# Add SDL2_ttf library
find_package(SDL2_ttf REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::TTF)