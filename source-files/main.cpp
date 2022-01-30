#include <iostream>
#include "../header-files/Bus.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Bus bus;
    bus.write(0x0000, 48);
    std::cout << bus.read(0x0000, false) << "\n";;
    bus.write(0x0001, 0x0001);
    std::cout << bus.read(0x0001, false) << "\n";
    if((0x80 & 0xA0)){
        std::cout << "hello world";
    }

    char exitChar = 0;

    while(exitChar != 'f'){
        std::cout << "enter 'f' to stop cycle emulation\n";
        std::cin >> exitChar;
    }

    return 0;

}
