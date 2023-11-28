#include "headers/player.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "headers/globals.h"
#include "headers/bullets.h"
#include <stdio.h>

Player player;

SDL_Rect playerRect;

void initPlayer() {
    player.speed = 200.0;
    player.position.x = screenWidth/2 -50;
    player.position.y = screenHeight/2 -50;
    player.size.x = 100;
    player.size.y = 100;
    player.rotation = 0;
    player.reloadTime = 0.5;
    player.currentReloadTimer = 0;
    playerRect.x = player.position.x;
    playerRect.y = player.position.y;
    playerRect.w = player.size.x;
    playerRect.h = player.size.y;
    player.direction.x = 0;
    player.direction.y = 0;
    player.health = 100;
}

void playerInput(const Uint8* keyboardState) {
    player.direction = (Vector2){keyboardState[SDL_SCANCODE_D] - keyboardState[SDL_SCANCODE_A], keyboardState[SDL_SCANCODE_S] - keyboardState[SDL_SCANCODE_W]};
}

void movePlayer() {
    player.position.x += normalizeVector(player.direction).x * deltaTime * player.speed;
    player.position.y += normalizeVector(player.direction).y * deltaTime * player.speed;
    if (player.position.x > screenWidth - player.size.x) player.position.x = screenWidth - player.size.x;
    if (player.position.x < 0) player.position.x = 0;
    if (player.position.y > screenHeight - player.size.y) player.position.y = screenHeight - player.size.y;
    if (player.position.y < 0) player.position.y = 0;
}

void playerMouseInput() {
    Uint32 mouseState = SDL_GetMouseState(&player.mouseX, &player.mouseY);
    if (mouseState == SDL_BUTTON(1) && player.currentReloadTimer <= 0) {
        Vector2 mousePosition;
        mousePosition.x = player.mouseX;
        mousePosition.y = player.mouseY;
        createBullet(addVectors(player.position, (Vector2){50, 50}), mousePosition);
        player.currentReloadTimer = player.reloadTime;
    }
}

void updatePlayer() {
    if (player.currentReloadTimer > 0) {
        player.currentReloadTimer -= deltaTime;
    }
    player.rotation++;
    if (player.rotation > 360) player.rotation -= 360;
}

void drawPlayer(SDL_Renderer* renderer, SDL_Texture* sprite) {
    playerRect.x = player.position.x;
    playerRect.y = player.position.y; 
    if (SDL_RenderCopyEx(renderer, sprite, NULL, &playerRect, player.rotation, NULL, SDL_FLIP_NONE)!= 0) {
        printf(SDL_GetError());
    } // draw player   
}

Player* getPlayer() {
    return &player;
}