#include "headers/input.h"

Uint8* keysDown;
Uint8* keysUp;
int numkeys;

Uint8* mouseDown;
Uint8* mouseUp;
Vector2 mousePos;

void setupInput() {
    SDL_GetKeyboardState(&numkeys);
    keysDown = (Uint8*)calloc(numkeys, sizeof(Uint8));
    keysUp = (Uint8*)calloc(numkeys, sizeof(Uint8));

    mouseDown = (Uint8*)calloc(5, sizeof(Uint8));
    mouseUp = (Uint8*)calloc(5, sizeof(Uint8));
}

void buttonDownEvent(SDL_Scancode key) {
    keysDown[key] = 1;
}

void buttonUpEvent(SDL_Scancode key) {
    keysUp[key] = 1;
}

void mouseButtonDownEvent(int button) {
    mouseDown[button-1] = 1;
}
void mouseButtonUpEvent(int button) {
    mouseUp[button-1] = 1;
}

void resetKeysUpDown() {
    int i;
    for (i = 0; i < numkeys; i++) {
        keysDown[i] = 0;
        keysUp[i] = 0;
    }
    int j;
    for (j = 0; j < 5; j++) {
        mouseDown[j] = 0;
        mouseUp[j] = 0;
    }
}

int getKeyDown(SDL_Scancode key) {
    return keysDown[key];
}

int getKey(SDL_Scancode key) {
    return SDL_GetKeyboardState(NULL)[key];
}

int getKeyUp(SDL_Scancode key) {
    return keysUp[key];
}

int getMouseButtonDown(int button) {
    return mouseDown[button-1];
}

int getMouseButton(int button) {
    return (SDL_BUTTON(button) & SDL_GetMouseState(NULL, NULL) == SDL_BUTTON(button));
}

int getMouseButtonUp(int button) {
    return mouseUp[button-1];
}

int mouseInputX, mouseInputY;

Vector2 getMousePosition() {
    SDL_GetMouseState(&mouseInputX, &mouseInputY);
    mousePos.x = mouseInputX;
    mousePos.y = mouseInputY;
    return mousePos;
}