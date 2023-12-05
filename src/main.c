#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <time.h>
#include "headers/vector.h"
#include "headers/bullets.h"
#include "headers/globals.h"
#include "headers/player.h"
#include "headers/enemy.h"
#include "headers/collisions.h"
#include "headers/textureManager.h"
#include "headers/healthbar.h"
#include "headers/score.h"
#include "headers/gameState.h"
#include "headers/button.h"

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
    TTF_Init();
    setupButtons(renderer);
    setGameState(0);
}

void quit() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);
    SDL_Quit();
}

void initGame() {
    initPlayer();
    setupHealthbar(renderer);
    setupScore(renderer);
    restartGame();
}

void restartGame() {
    destroyAllBullets();
    destroyAllEnemies();
    resetScore();
    initPlayer();
}

void gameLoop() {
    int running = TRUE;
    int t = SDL_GetTicks();
    int fps = 0;
    int numFrames = 0;
    int lastFrameStartTime;

    SDL_Texture* playerSprite = createTexture("content/sprites/player1.png", renderer);
    SDL_Texture* enemySprite = createTexture("content/sprites/enemy1.png", renderer);

    Button startGameButton = createButton((Vector2){screenWidth/2.0-250, screenHeight/2.0-50}, (Vector2){500, 100}, "start", 0);
    Button menuButton = createButton((Vector2){screenWidth/2.0-250, screenHeight/2.0+50}, (Vector2){500, 100}, "menu", 1);
    Button unpauseButton = createButton((Vector2){screenWidth/2.0-250, screenHeight/2.0-150}, (Vector2){500, 100}, "back", 2);

    int gameStarted = 0;

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

        // gamestate:
        // 0 - main menu
        // 1 - pause
        // 2 - playing
        if (getGameState() == 0) {
            if (gameStarted == 1) {
                gameStarted = 0;
            }
            updateButton(startGameButton);
            drawButton(startGameButton, renderer);
        }
        if (getGameState() >= 1) {
            if (gameStarted == 0) {
                initGame();
                currentEnemySpawnTimeWait = maxEnemySpawnTimeWait;
                gameStarted = 1;
            }
            if (getGameState() == 2) {
                updatePlayer();
                playerInput(SDL_GetKeyboardState(NULL));
                playerMouseInput();
                movePlayer();

                updateAllBullets();
                updateEveryEnemy(getPlayer()->position);

                updateHealthbar(getPlayer()->health, getPlayer()->maxHealth);

                int b;
                int e;
                for (e = 0; e < getEnemyCount(); e++) {
                        for (b = 0; b < getBulletCount(); b++) {
                            checkBulletToEnemy(getBulletAt(b), getEnemyAt(e));
                        }
                        checkPlayerToEnemy(getPlayer(), getEnemyAt(e));
                }

                if (getPlayer()->health <= 0) {
                    restartGame();
                }
                
                if (currentEnemySpawnTimeWait <= 0) {
                    spawnEnemy();
                    currentEnemySpawnTimeWait = maxEnemySpawnTimeWait;
                }
                currentEnemySpawnTimeWait -= deltaTime;
            } 

            drawEveryEnemy(renderer, enemySprite);
            drawPlayer(renderer, playerSprite);
            drawAllBullets(renderer, playerSprite);
            drawHealthbar(renderer);
            drawHealthbarText(renderer);
            drawScore(renderer);
            
            if (getGameState() == 1) {
                updateButton(menuButton);
                updateButton(unpauseButton);
                drawButton(menuButton, renderer);
                drawButton(unpauseButton, renderer);
            }

            if (getGameState() == 2) {
                if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE]) {
                    setGameState(1);
                }
            }
        }

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