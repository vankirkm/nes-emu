#include <iostream>
#include "../header-files/Bus.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Bus bus;
    bus.write(0x0000, 1);
    std::cout << bus.read(0x0000, false);
    bus.write(0x0001, 0x0001);
    std::cout << bus.read(0x0001, false);
    return 0;

}
