#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <time.h>
#include "headers/vector.h"
#include "headers/bullets.h"
#include "headers/globals.h"
#include "headers/player.h"
#include "headers/enemy.h"
#include "headers/collisions.h"

#define FALSE 0
#define TRUE 1

#define WINDOW_TITLE "SDL Game"

SDL_Window* screen = NULL;
SDL_Renderer* renderer;

void init() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(screenWidth, screenHeight, SDL_WINDOW_SHOWN, &screen, &renderer);
    SDL_SetWindowTitle(screen, WINDOW_TITLE);
    srand(time(NULL));
    initPlayer();
}

void loadImage(SDL_Texture* texture, char* path) {
    SDL_Surface* surface = IMG_Load(path);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    printf(SDL_GetError());
}

SDL_Texture* createTexture(char* path) {
    SDL_Surface* surface = IMG_Load(path);
    return SDL_CreateTextureFromSurface(renderer, surface);
}

void quit() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);
    SDL_Quit();
}

void restartGame() {
    destroyAllBullets();
    destroyAllEnemies();
    initPlayer();
}

void gameLoop() {
    int running = TRUE;
    int t = SDL_GetTicks();
    int fps = 0;
    int numFrames = 0;
    int lastFrameStartTime;

    SDL_Texture* playerSprite = createTexture("content/sprites/player1.png");
    SDL_Texture* enemySprite = createTexture("content/sprites/enemy1.png");

    float maxEnemySpawnTimeWait = 1;
    float currentEnemySpawnTimeWait = maxEnemySpawnTimeWait;

    while (running) {
        while (SDL_GetTicks() - lastFrameStartTime < (float)1000/(float)TARGET_FPS) {
            continue;
        }
        deltaTime = (SDL_GetTicks() - lastFrameStartTime) / 1000.0;
        lastFrameStartTime = SDL_GetTicks();
        if (lastFrameStartTime - t > 1000) {
            t = lastFrameStartTime;
            fps = numFrames;
            numFrames = 0;
        }

        // input handling
        SDL_Event event;
        SDL_PollEvent(&event);
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
                case SDL_QUIT:
                {
                    running = FALSE;
                    break;  
                }
                case SDL_KEYDOWN:
                {
                    if (event.key.repeat == 0) {

                    }
                }
			}
		}

        // clear the screen before drawing anything again
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // game logic
        updatePlayer();
        playerInput(SDL_GetKeyboardState(NULL));
        playerMouseInput();
        movePlayer();

        updateAllBullets();
        updateEveryEnemy(getPlayer()->position);

        int b;
        int e;
        for (e = 0; e < getEnemyCount(); e++) {
            if (getEnemyAt(e) != NULL) {
                for (b = 0; b < getBulletCount(); b++) {
                    if (getBulletAt(b) != NULL) checkBulletToEnemy(getBulletAt(b), getEnemyAt(e));
                    else printf("AAAAAAAAAAAAAAA BULLET NULL ");
                }
                checkPlayerToEnemy(getPlayer(), getEnemyAt(e));
            } else printf("AAAAAAAAAAAAAA ENEMY NULL ");
        }

        if (getPlayer() == NULL) printf("AAAAAAAAAAAAAA PLAYER NULL ");

        if (getPlayer()->health <= 0) {
            restartGame();
        }

        drawEveryEnemy(renderer, enemySprite);
        drawPlayer(renderer, playerSprite);
        drawAllBullets(renderer, playerSprite);
        
        if (currentEnemySpawnTimeWait <= 0) {
            spawnEnemy();
            currentEnemySpawnTimeWait = maxEnemySpawnTimeWait;
        }
        currentEnemySpawnTimeWait -= deltaTime;

        // change the window title to show FPS
        char s[50];
        sprintf(s, "%s FPS: %d", WINDOW_TITLE, fps);
        SDL_SetWindowTitle(screen, s);

        // actually draw on the screen
        SDL_RenderPresent(renderer);
        numFrames++;
    }
}

int main(int argc, char* args[]) {
    init();
    gameLoop();
    quit();

    return 0;
}