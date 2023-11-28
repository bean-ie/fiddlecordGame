#ifndef PLAYER_H
#define PLAYER_H

#include <math.h>
#include "vector.h"
#include "SDL2/SDL.h"

struct Player {
    Vector2 position;
    Vector2 size;
    Vector2 direction;
    float speed;
    int rotation;
    int mouseX;
    int mouseY;
    float reloadTime, currentReloadTimer;
    int health;
};

typedef struct Player Player;

void initPlayer();

void playerInput(const Uint8* keyboardState);
void movePlayer();
void playerMouseInput();
void updatePlayer();

void drawPlayer(SDL_Renderer* renderer, SDL_Texture* sprite);

Player* getPlayer();

#endif