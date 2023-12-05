#ifndef SCORE_H
#define SCORE_H

typedef struct SDL_Renderer SDL_Renderer;

void setupScore(SDL_Renderer* renderer);

void addScore(int amount);
void resetScore();

void drawScore(SDL_Renderer* renderer);

#endif