#include <iostream>
#include "../header-files/Bus.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include <filesystem>

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800

int main() {

    SDL_Init(SDL_INIT_VIDEO);

    if(TTF_Init() == -1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }

    SDL_Window *window = SDL_CreateWindow("NES Emulator", 0, 0,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);

    // debug text block
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);



    TTF_Font* Sans = TTF_OpenFont("../8bitregular.ttf", 24);
    SDL_Color White = {255, 255, 255};
    if(!Sans) {
        printf("font failed: %s\n", TTF_GetError());
    }
    // as TTF_RenderText_Solid could only be used on
    // SDL_Surface then you have to create the surface first
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "hello world", White);

    if(!surfaceMessage) {
        printf("render text failed: %s\n", TTF_GetError());
    }

    // now convert it into a texture
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 0;  //controls the rect's x coordinate
    Message_rect.y = 0; // controls the rect's y coordinte
    Message_rect.w = 200; // controls the width of the rect
    Message_rect.h = 100; // controls the height of the rect


    SDL_ShowWindow(window);

    SDL_Event event;
    int running = 1;
    while(running) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);//red. Was testing to see if window would open red and change to green then blue but this doesn't work.
        SDL_RenderClear(renderer);
        if (SDL_RenderCopy(renderer, Message, nullptr, &Message_rect) != 0)
        {
            std::cout << "(Tilemap) SDL_RenderCopy Error: " << SDL_GetError() << std::endl;
        }
        while(SDL_PollEvent(&event)) {

            if(event.type == SDL_QUIT) {
                running = 0;
            }

        }
        SDL_RenderPresent(renderer);
        SDL_Delay( 32 );
    }
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
    SDL_DestroyRenderer(renderer);
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
