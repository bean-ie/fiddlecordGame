#ifndef INPUT_H
#define INPUT_H

#include "SDL2/SDL.h"
#include "vector.h"

void setupInput();

void buttonDownEvent(SDL_Scancode key);
void buttonUpEvent(SDL_Scancode key);

void mouseButtonDownEvent(int button);
void mouseButtonUpEvent(int button);

void resetKeysUpDown();

int getKeyDown(SDL_Scancode key);
int getKey(SDL_Scancode key);
int getKeyUp(SDL_Scancode key);

int getMouseButtonDown(int button);
int getMouseButton(int button);
int getMouseButtonUp(int button);
Vector2 getMousePosition();

#endif