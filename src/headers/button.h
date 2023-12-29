#ifndef BUTTON_H
#define BUTTON_H

#include "vector.h"
typedef struct SDL_Renderer SDL_Renderer;
struct Button {
    Vector2 position;
    Vector2 size;
    char* text;
    int id;
    int pressed;
};

typedef struct Button Button;

void setupButtons();
Button createButton(Vector2 position, Vector2 size, char* text, int id);

void updateButton(Button* button);
void drawButton(Button button);

void buttonClick(int id);

#endif