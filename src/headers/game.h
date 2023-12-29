#ifndef GAME_H
#define GAME_H

#include "button.h"
#include "playerClass.h"
typedef struct SDL_Renderer SDL_Renderer;

void setUpGame(SDL_Renderer* _renderer);
void selectClass(PlayerClass _class);
void initGame();
void restartGame();

void gameLoop();

void updateAndDrawButton(Button* button);
void updateEverything();
void drawEverything();

#endif