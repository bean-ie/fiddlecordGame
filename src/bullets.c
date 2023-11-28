#include "headers/bullets.h"
#include "headers/globals.h"

Bullet bullets[100];
int bulletCount = 0;

void createBullet(Vector2 spawnPosition, Vector2 mousePosition) {
    if (bulletCount > 99) {
            destroyBullet(0);
        }
    Vector2 direction = subtractVectors(mousePosition, spawnPosition);
    Bullet bulletToSpawn;
    bulletToSpawn.position.x = spawnPosition.x - 25;
    bulletToSpawn.position.y = spawnPosition.y - 25;
    bulletToSpawn.lifeTime = 2;
    bulletToSpawn.damage = 150;
    bulletToSpawn.speed = 600;
    bulletToSpawn.direction = direction;
    bullets[bulletCount] = bulletToSpawn;
    bulletCount++;
}

void destroyBullet(int bulletIndex) {
    int i;
    for (i = bulletIndex; i < 99; i++) {
        bullets[i] = bullets[i + 1];
    }
    bulletCount--;  
}

void destroyAllBullets() {
    memset(bullets, 0, sizeof(bullets));
}

void updateAllBullets() {
    int i;
        for (i = 0; i < bulletCount; i++) {
            if (bullets[i].damage <= 0 || bullets[i].lifeTime <= 0) destroyBullet(i);
            bullets[i].position = addVectors(bullets[i].position, multiplyVector(multiplyVector(normalizeVector(bullets[i].direction), deltaTime), bullets[i].speed));
            bullets[i].lifeTime -= deltaTime;
        }
}

void drawAllBullets(SDL_Renderer* renderer, SDL_Texture* sprite) {  
    SDL_Rect bulletToDrawRect = {0, 0, 50, 50};
    int i;
    for (i = 0; i < bulletCount; i++) {
        bulletToDrawRect.x = bullets[i].position.x;
        bulletToDrawRect.y = bullets[i].position.y;
        SDL_RenderCopy(renderer, sprite, NULL, &bulletToDrawRect);
    }    
}

Bullet* getBulletAt(int index) {
    return &bullets[index];
}

int getBulletCount() {
    return bulletCount;
}