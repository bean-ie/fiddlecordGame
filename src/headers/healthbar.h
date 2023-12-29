#ifndef HEALTHBAR_H
#define HEALTHBAR_H
#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>

void setupHealthbar();

void updateHealthbar(int health, int maxHealth);

void drawHealthbar();
void drawHealthbarText();

#endif