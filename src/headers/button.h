#ifndef BUTTON_H
#define BUTTON_H

#include "vector.h"
typedef struct SDL_Renderer SDL_Renderer;
struct Button {
    Vector2 position;
    Vector2 size;
    char* text;
    int id;
};

typedef struct Button Button;

void setupButtons(SDL_Renderer* renderer);
Button createButton(Vector2 position, Vector2 size, char* text, int id);

void updateButton(Button button);
void drawButton(Button button, SDL_Renderer* renderer);

void buttonClick(int id);

#endif