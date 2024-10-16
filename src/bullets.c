#include "headers/bullets.h"
#include "headers/globals.h"
#include "headers/textureManager.h"
#include "headers/player.h"
#include "headers/playerClass.h"
#include "headers/classAbilities.h"

Bullet bullets[100];
int bulletCount = 0;

SDL_Texture* bulletSprite;

void setupBullets() {
    bulletSprite = createTexture("content/sprites/player1.png");
}

void createBullet(Vector2 spawnPosition, Vector2 direction) {
    if (bulletCount > 99) {
            destroyBullet(99);
        }
    Bullet bulletToSpawn;
    bulletToSpawn.active = 1;
    bulletToSpawn.position.x = spawnPosition.x - 25;
    bulletToSpawn.position.y = spawnPosition.y - 25;
    bulletToSpawn.lifeTime = getPlayer()->class.bulletLifetime;
    bulletToSpawn.damage = getPlayer()->class.damage;
    bulletToSpawn.speed = randomMinMax(500, 700);
    bulletToSpawn.direction = normalizeVector(direction);
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
            if (bullets[i].damage <= 0 || bullets[i].lifeTime <= 0) {
                switch (getPlayer()->class.id) {
                    default:
                        destroyBullet(i);
                    break;

                    case 4:
                        bullets[i].direction = normalizeVector(subtractVectors(getPlayer()->position, bullets[i].position));
                        if (sqrMagnitude(subtractVectors(getPlayer()->position, bullets[i].position)) <= 100*100) {
                            ryanReplenishAmmo(0);
                            destroyBullet(i);
                        }
                    break;
                }
            }
            bullets[i].position = addVectors(bullets[i].position, multiplyVector(multiplyVector(bullets[i].direction, deltaTime), bullets[i].speed));
            bullets[i].lifeTime -= deltaTime;
        }
}

void drawAllBullets() {  
    SDL_Rect bulletToDrawRect;
    int i;
    for (i = 0; i < bulletCount; i++) {
        bulletToDrawRect.x = bullets[i].position.x;
        bulletToDrawRect.y = bullets[i].position.y;
        bulletToDrawRect.w = 50;
        bulletToDrawRect.h = 50;
        render(bulletSprite, &bulletToDrawRect);
    }
}

Bullet* getBulletAt(int index) {
    return &bullets[index];
}

int getBulletCount() {
    return bulletCount;
}