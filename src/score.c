#include "headers/score.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "headers/textureManager.h"
#include "headers/globals.h"

int score;
SDL_Rect scoreBackRect, scoreTextRect;
SDL_Texture* scoreBackSprite;
TTF_Font* scoreFont;
SDL_Color scoreTextColor;

void setupScore(SDL_Renderer* renderer) {
    score = 0;
    scoreBackSprite = createTexture("content/sprites/scoreBack.png", renderer);
    scoreFont = TTF_OpenFont("content/fonts/Square.ttf", 48);
    scoreTextColor.r = 255;
    scoreTextColor.g = 255;
    scoreTextColor.b = 255;
}

void addScore(int amount) {
    score += amount;
}

void resetScore() {
    score = 0;
}

void drawScore(SDL_Renderer* renderer) {
    char* message[6];
    sprintf(message, "%i", score);
    Text text = createText(scoreFont, message, scoreTextColor, renderer);
    scoreTextRect.x = screenWidth/2 - text.w/2;
    scoreTextRect.y = 45;
    scoreTextRect.w = text.w;
    scoreTextRect.h = text.h;
    scoreBackRect.w = text.w + 50;
    scoreBackRect.h = text.h + 20;
    scoreBackRect.x = scoreTextRect.x - 25;
    scoreBackRect.y = scoreTextRect.y - 10;
    SDL_RenderCopy(renderer, scoreBackSprite, NULL, &scoreBackRect);
    SDL_RenderCopy(renderer, text.texture, NULL, &scoreTextRect);
}