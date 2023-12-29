#include "headers/collisions.h"
#include "headers/bullets.h"
#include "headers/enemy.h"
#include "headers/player.h"
#include "headers/vector.h"
#include "headers/score.h"

int collides(Vector2 firstPos, Vector2 firstSize, Vector2 secondPos, Vector2 secondSize) {
    if (firstPos.x < secondPos.x + secondSize.x &&
        firstPos.x + firstSize.x > secondPos.x &&
        firstPos.y < secondPos.y + secondSize.y &&
        firstPos.y  + firstSize.y > secondPos.y ) 
        return 1;
        else return 0;
}

void checkBulletToEnemy(Bullet* bullet, Enemy* enemy) {
    if (sqrMagnitude(subtractVectors(enemy->position, bullet->position)) <= 300*300) {
        if (collides(bullet->position, (Vector2){50, 50}, enemy->position, enemy->size)) {
            int damageDealt = enemy->health;
            if (damageDealt > bullet->damage) damageDealt = bullet->damage; 
            enemy->health -= bullet->damage;
            bullet->damage -= damageDealt;
            if (enemy->health <= 0) addScore(1);
        }
    }
}

void checkPlayerToEnemy(Player* player, Enemy* enemy) {
    if (sqrMagnitude(subtractVectors(enemy->position, player->position)) <= 300*300) {
        if (collides(player->position, player->class.size, enemy->position, enemy->size)) {
            player->health -= enemy->damage;
            enemy->health = 0;
        }
    }
}