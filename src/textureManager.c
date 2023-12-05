#include "headers/textureManager.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

SDL_Texture* createTexture(char* path, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(path);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

Text createText(TTF_Font* font, char* message, SDL_Color color, SDL_Renderer* renderer) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, message, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    Text text;
    text.texture = texture;
    if (TTF_SizeUTF8(font, message, &text.w, &text.h) != 0) { 
        //printf("wtf error %s", SDL_GetError());
    }
    SDL_FreeSurface(surface);
    return text;
}