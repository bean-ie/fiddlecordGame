#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <time.h>
#include "headers/globals.h"
#include "headers/game.h"
#include "headers/input.h"
#include "headers/classSelectionMenu.h"

#define WINDOW_TITLE "Fiddlecord Game"

SDL_Window* screen = NULL;
SDL_Renderer* mainRenderer;

void init() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(screenWidth, screenHeight, SDL_WINDOW_SHOWN, &screen, &mainRenderer);
    SDL_SetWindowTitle(screen, WINDOW_TITLE);
    srand(time(NULL));
    TTF_Init();
    setupInput();
    setupTextures(mainRenderer);
    createClasses();
    setupButtons();
    setupGame(mainRenderer);
}

void quit() {
    SDL_DestroyRenderer(mainRenderer);
    SDL_DestroyWindow(screen);
    SDL_Quit();
}

int main(int argc, char* args[]) {
    init();
    gameLoop();
    quit();

    return 0;
}