#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

struct Text {
    SDL_Texture* texture;
    int w;
    int h;
};
typedef struct Text Text;

void setupTextures(SDL_Renderer* _renderer);
SDL_Texture* createTexture(char* path);
Text createText(TTF_Font* font, char* message, SDL_Color color);

void render(SDL_Texture* texture, SDL_Rect* rect);
void renderEx(SDL_Texture* texture, SDL_Rect* rect, double angle, SDL_Point* center);

#endif