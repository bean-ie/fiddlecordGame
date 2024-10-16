#include "headers/player.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "headers/globals.h"
#include "headers/bullets.h"
#include "headers/input.h"
#include "headers/classAbilities.h"
#include <stdio.h>

Player player;

SDL_Rect playerRect;

void initPlayer(PlayerClass class) {
    player.class = class;
    player.speed = 200.0;
    player.position.x = screenWidth/2 -50;
    player.position.y = screenHeight/2 -50;
    player.velocity = (Vector2){0, 0};
    player.acceleration = (Vector2){0, 0};
    player.rotation = 0;
    player.currentReloadTimer = 0;
    playerRect.x = player.position.x;
    playerRect.y = player.position.y;
    playerRect.w = player.class.size.x;
    playerRect.h = player.class.size.y;
    player.direction.x = 0;
    player.direction.y = 0;
    player.health = player.class.maxHealth;
}

void playerInput() {
    //player.direction = (Vector2){getKey(SDL_SCANCODE_D) - getKey(SDL_SCANCODE_A), getKey(SDL_SCANCODE_S) - getKey(SDL_SCANCODE_W)};
    Vector2 force = {0, 0};
    force.x = (getKey(SDL_SCANCODE_D) - getKey(SDL_SCANCODE_A));
    force.y = (getKey(SDL_SCANCODE_S) - getKey(SDL_SCANCODE_W));
    force = normalizeVector(force);
    force = multiplyVector(force, 300.0);
    addForce(force);
}

void movePlayer() {
    // Player movement, iteration 1
    //player.position.x += normalizeVector(player.direction).x * deltaTime * player.speed * player.class.speedModifier;
    //player.position.y += normalizeVector(player.direction).y * deltaTime * player.speed * player.class.speedModifier;

    // Player movement, iteration 2
    ///*
    player.velocity = addVectors(player.velocity, multiplyVector(player.acceleration, deltaTime));
    player.position.x += player.velocity.x * deltaTime;
    player.position.y += player.velocity.y * deltaTime;
    player.velocity = multiplyVector(player.velocity, 0.9);
    player.acceleration = multiplyVector(player.acceleration, 0.9);
    //*/

    // Player movement, iteration 3
    /*
    addForce(multiplyVector(normalizeVector(player.velocity), -0.6 * 1000));
    player.acceleration = divideVector(player.allForces, player.mass);
    player.velocity = addVectors(player.velocity, multiplyVector(player.acceleration, deltaTime));
    player.position.x += player.velocity.x * deltaTime * player.class.speedModifier;
    player.position.y += player.velocity.y * deltaTime * player.class.speedModifier;
    player.allForces = (Vector2){0, 0}; 
    */

    // screen clamping
    if (player.position.x > screenWidth - player.class.size.x) { 
        player.position.x = screenWidth - player.class.size.x;
        player.velocity.x = 0;
    }
    if (player.position.x < 0) { 
        player.position.x = 0;
        player.velocity.x = 0;
    }
    if (player.position.y > screenHeight - player.class.size.y) {
        player.position.y = screenHeight - player.class.size.y;
        player.velocity.y = 0;
    }
    if (player.position.y < 0) {
        player.position.y = 0;
        player.velocity.y = 0;
    }
}

void addForce(Vector2 force) { 
    player.acceleration = addVectors(player.acceleration, divideVector(force, player.class.mass));
    //player.allForces = addVectors(player.allForces, force);
}

void playerMouseInput() {
    if (getMouseButton(1) && player.currentReloadTimer <= 0) {
        player.currentReloadTimer = player.class.reloadTime;
        if (onShootAbility() == 0) return;
        Vector2 mousePosition;
        mousePosition.x = getMousePosition().x;
        mousePosition.y = getMousePosition().y;
        float angle;
        int i;
        for (i = 0; i < player.class.bulletsPerShot; i++) {
            angle = randomMinMax(-player.class.bulletSpreadAngle/2, player.class.bulletSpreadAngle/2);
            createBullet(addVectors(player.position, (Vector2){50, 50}), rotateVector(normalizeVector(subtractVectors(mousePosition, addVectors(player.position, multiplyVector(player.class.size, 0.5)))), angle));
        }
        addForce(multiplyVector(normalizeVector(subtractVectors(getMousePosition(), addVectors(player.position, divideVector(player.class.size, 2)))), -player.class.shotKnockbackForce));
    }
}

void updatePlayer() {
    if (player.currentReloadTimer > 0) {
        player.currentReloadTimer -= deltaTime;
    }
    //player.rotation++;
    //if (player.rotation > 360) player.rotation -= 360;
    abilityLoop();
}

void drawPlayer() {
    playerRect.x = player.position.x;
    playerRect.y = player.position.y; 
    render(player.class.sprite, &playerRect);
}

Player* getPlayer() {
    return &player;
}