#include "headers/healthbar.h"
#include "SDL2/SDL.h"
#include "headers/textureManager.h"
#include "SDL2/SDL_ttf.h"

SDL_Rect healthbarRect, backRect, textRect;
SDL_Texture* healthbarSprite;
SDL_Texture* backSprite;
TTF_Font* font;
SDL_Color textColor;
int maxHealth, health;

void setupHealthbar() {
    healthbarRect.x = 50;
    healthbarRect.y = 50;
    healthbarRect.w = 300;
    healthbarRect.h = 60;
    backRect.x = 35;
    backRect.y = 35;
    backRect.w = 330;
    backRect.h = 90;
    healthbarSprite = createTexture("content/sprites/healthbar.png");
    backSprite = createTexture("content/sprites/healthbarBack.png");
    font = TTF_OpenFont("content/fonts/Square.ttf", 48);
    textColor.r = 255;
    textColor.g = 255;
    textColor.b = 255;
}

void updateHealthbar(int _health, int _maxHealth) {
    health = _health;
    maxHealth = _maxHealth;
}

void drawHealthbar() {
    healthbarRect.w = 300.0 * (float)health/maxHealth;
    render(backSprite, &backRect);
    render(healthbarSprite, &healthbarRect);
}

void drawHealthbarText() {
    char* message[10];
    sprintf(message, "%i/%i", health, maxHealth);
    Text text = createText(font, message, textColor);
    textRect.x = 200 - text.w/2;
    textRect.y = 80 - text.h/2;
    textRect.w = text.w;
    textRect.h = text.h;
    render(text.texture, &textRect);
    SDL_DestroyTexture(text.texture);
}