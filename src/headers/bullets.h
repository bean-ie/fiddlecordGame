#ifndef BULLET_H
#define BULLET_H

#include "vector.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct Bullet {
    Vector2 position;
    Vector2 direction;
    float speed;
    int damage;
    float lifeTime;
};

typedef struct Bullet Bullet;

Bullet* getBulletAt(int index);
int getBulletCount();

void createBullet(Vector2 spawnPosition, Vector2 mousePosition);
void destroyBullet(int bulletIndex);
void destroyAllBullets();

void updateAllBullets();
void drawAllBullets(SDL_Renderer* renderer, SDL_Texture* sprite);

#endif