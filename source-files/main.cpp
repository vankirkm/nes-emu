#include <iostream>
#include "../header-files/Bus.h"
#include "SDL2/SDL.h"

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800

int main() {

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("NES Emulator", 0, 0,
                                          SCREEN_HEIGHT, SCREEN_WIDTH, SDL_WINDOW_HIDDEN);
    SDL_ShowWindow(window);
    SDL_Event event;
    int running = 1;
    while(running) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = 0;
            }
        }
        SDL_Delay( 32 );
    }
    SDL_DestroyWindow(window);
    SDL_Quit();



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
