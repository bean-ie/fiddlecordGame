#ifndef HEALTHBAR_H
#define HEALTHBAR_H
#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>

void setupHealthbar(SDL_Renderer* renderer);

void updateHealthbar(int health, int maxHealth);

void drawHealthbar(SDL_Renderer* renderer);
void drawHealthbarText(SDL_Renderer* renderer);

#endif