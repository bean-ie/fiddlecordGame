#ifndef SCORE_H
#define SCORE_H

typedef struct SDL_Renderer SDL_Renderer;

void setupScore();

void addScore(int amount);
void resetScore();

void drawScore();

#endif