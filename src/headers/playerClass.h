#ifndef PLAYERCLASS_H
#define PLAYERCLASS_H

#include "vector.h"

typedef struct SDL_Texture SDL_Texture;
typedef struct SDL_Renderer SDL_Renderer;

struct PlayerClass {

    char* name;
    SDL_Texture* sprite;
    
    int maxHealth;

    Vector2 size;
    float mass;
    float shotKnockbackForce;

    float bulletSpreadAngle;
    int bulletsPerShot;

    float reloadTime;
    int damage;
};

typedef struct PlayerClass PlayerClass;

#endif