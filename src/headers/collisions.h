#ifndef COLLISIONS_H
#define COLLISIONS_H

typedef struct Bullet Bullet;
typedef struct Enemy Enemy;
typedef struct Player Player;
typedef struct Vector2 Vector2;

int collides(Vector2 firstPos, Vector2 firstSize, Vector2 secondPos, Vector2 secondSize);
void checkBulletToEnemy(Bullet* bullet, Enemy* enemy);
void checkPlayerToEnemy(Player* player, Enemy* enemy);

#endif