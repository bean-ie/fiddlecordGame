#include "headers/enemy.h"
#include "math.h"
#include "headers/globals.h"
#include "headers/textureManager.h"

Enemy enemies[100];
int enemyCount = 0;

SDL_Texture* enemySprite;
SDL_Texture* enemyCloseDeadSprite;

void setupEnemies() {
    enemySprite = createTexture("content/sprites/enemy1.png");
    enemyCloseDeadSprite = createTexture("content/sprites/enemy2.png");
}

void spawnEnemy() {
    if (enemyCount > 99) {
        destroyEnemy(99); 
    }
    struct Enemy enemyToSpawn;
    float randomAngle = random(360) * M_PI/180;
    enemyToSpawn.position.x = cos(randomAngle) * 1000 + screenWidth/2;
    enemyToSpawn.position.y = sin(randomAngle) * 1000 + screenHeight/2;
    enemyToSpawn.baseSpeed = 100.0;
    enemyToSpawn.speedMultiplier = (randomMinMax(5, 15)) / 10.0;
    enemyToSpawn.maxHealth = randomMinMax(100, 400);
    enemyToSpawn.health = enemyToSpawn.maxHealth;
    enemyToSpawn.damage = randomMinMax(5, 25);
    enemyToSpawn.size.x = 100 * (enemyToSpawn.maxHealth / 250);
    enemyToSpawn.size.y = 100 * (enemyToSpawn.maxHealth / 250);
    enemyToSpawn.moveSpeed = enemyToSpawn.baseSpeed * enemyToSpawn.speedMultiplier * (250 / enemyToSpawn.maxHealth);
    enemies[enemyCount] = enemyToSpawn;
    enemyCount += 1;
}

void updateEveryEnemy(Vector2 playerPosition) {
    int i;
    for (i = 0; i < enemyCount; i++) {
        if (enemies[i].health <= 0) destroyEnemy(i);
        enemies[i].direction = normalizeVector(subtractVectors(playerPosition, addVectors(enemies[i].position, (Vector2){-50 + enemies[i].size.x/2, -50 + enemies[i].size.y/2})));
        enemies[i].position = addVectors(enemies[i].position, multiplyVector(multiplyVector(enemies[i].direction, deltaTime), enemies[i].moveSpeed));
    }
}

void drawEveryEnemy() {
    int i;
    for (i = 0; i < enemyCount; i++) {
        SDL_Rect enemyRect;
        enemyRect.x = (int)enemies[i].position.x;
        enemyRect.y = (int)enemies[i].position.y;
        enemyRect.w = (int)enemies[i].size.x;
        enemyRect.h = (int)enemies[i].size.y;
        SDL_Texture* spriteToUse;
        if (enemies[i].health <= enemies[i].maxHealth * 0.5) {
            spriteToUse = enemyCloseDeadSprite;
        } else {
            spriteToUse = enemySprite;
        }
        render(spriteToUse, &enemyRect);
    }
}

void destroyEnemy(int enemyIndex) {
    int i;
    for (i = enemyIndex; i < 99; i++) {
        enemies[i] = enemies[i + 1];
    }
    enemyCount--;
}

void destroyAllEnemies() {
    memset(enemies, 0, sizeof(enemies));
}

Enemy* getEnemyAt(int index) {
    return &enemies[index];
}

int getEnemyCount() {
    return enemyCount;
}