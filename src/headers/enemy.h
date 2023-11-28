#ifndef ENEMY_H
#define ENEMY_H

#include "vector.h"
#include "SDL2/SDL.h"

struct Enemy {
    Vector2 position;
    Vector2 size;
    Vector2 direction;
    float baseSpeed, speedMultiplier, moveSpeed;
    float maxHealth, health;
    float damage;
};
typedef struct Enemy Enemy;

void spawnEnemy();
void updateEveryEnemy(Vector2 playerPosition);
void drawEveryEnemy(SDL_Renderer* renderer, SDL_Texture* sprite);

void destroyEnemy(int enemyIndex);
void destroyAllEnemies();

Enemy* getEnemyAt(int index);
int getEnemyCount();

#endif