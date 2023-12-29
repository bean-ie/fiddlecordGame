#ifndef PLAYER_H
#define PLAYER_H

#include <math.h>
#include "vector.h"
#include "SDL2/SDL.h"
#include "playerClass.h"

struct Player {
    Vector2 position;
    Vector2 direction;
    Vector2 velocity;
    Vector2 acceleration;
    float speed;
    int rotation;
    int mouseX;
    int mouseY;
    float currentReloadTimer;
    int health;
    PlayerClass class;
};

typedef struct Player Player;

void initPlayer(PlayerClass class);

void playerInput();
void addForce(Vector2 force);
void movePlayer();
void playerMouseInput();
void updatePlayer();

void drawPlayer();

Player* getPlayer();

#endif