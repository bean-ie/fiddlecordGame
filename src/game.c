#include "headers/game.h"
#include "SDL2/SDL.h"
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
#include "headers/input.h"
#include "headers/classSelectionMenu.h"

SDL_Renderer* gameRenderer;

void setupGame(SDL_Renderer* _renderer) {
    gameRenderer = _renderer;
}

PlayerClass class;

void selectClass(PlayerClass _class) { 
    class = _class;
}

void initGame() {
    initPlayer(class);
    setupHealthbar();
    setupScore();
    setupBullets();
    setupEnemies();
    restartGame();
}

void restartGame() {
    destroyAllBullets();
    destroyAllEnemies();
    resetScore();
    initPlayer(class);
}

float maxEnemySpawnTimeWait = 1;
float currentEnemySpawnTimeWait;

void gameLoop() {
    int running = 1;
    int t = SDL_GetTicks();
    int fps = 0;
    int numFrames = 0;
    int lastFrameStartTime;

    Button startGameButton = createButton((Vector2){screenWidth/2.0-250, screenHeight/2.0-50}, (Vector2){500, 100}, "start", 0);
    Button menuButton = createButton((Vector2){screenWidth/2.0-250, screenHeight/2.0+50}, (Vector2){500, 100}, "menu", 1);
    Button unpauseButton = createButton((Vector2){screenWidth/2.0-250, screenHeight/2.0-150}, (Vector2){500, 100}, "back", 2);

    int gameStarted = 0;

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
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
                case SDL_QUIT:
                {
                    running = 0;
                    break;  
                }
                case SDL_KEYDOWN:
                {
                    if (event.key.repeat == 0) {
                        buttonDownEvent(event.key.keysym.scancode);
                    }
                    break;
                }
                case SDL_KEYUP:
                {
                    buttonUpEvent(event.key.keysym.scancode);
                    break;
                }
                case SDL_MOUSEBUTTONDOWN:
                {
                    mouseButtonDownEvent(event.button.button);
                    break;
                }
                case SDL_MOUSEBUTTONUP:
                {
                    mouseButtonUpEvent(event.button.button);
                    break;
                }
			}
		}

        // clear the screen before drawing anything again
        SDL_SetRenderDrawColor(gameRenderer, 255, 255, 255, 255);
        SDL_RenderClear(gameRenderer);

        // game logic
        switch (getGameState()) {
            case Menu:
                if (gameStarted == 1) gameStarted = 0;
                updateAndDrawButton(&startGameButton);
                break;
            case Paused: 
                if (gameStarted == 0) {
                    initGame();
                    currentEnemySpawnTimeWait = maxEnemySpawnTimeWait;
                    gameStarted = 1;
                }
                drawEverything();
                updateAndDrawButton(&menuButton);
                updateAndDrawButton(&unpauseButton);
                if (getKeyDown(SDL_SCANCODE_ESCAPE)) {
                    setGameState(Running);
                }
                break;
            case Running:
                if (gameStarted == 0) {
                    initGame();
                    currentEnemySpawnTimeWait = maxEnemySpawnTimeWait;
                    gameStarted = 1;
                }
                updateEverything();
                drawEverything();
                if (getKeyDown(SDL_SCANCODE_ESCAPE)) {
                    setGameState(Paused);
                }
                break;
            case CharacterSelection:
                renderAndUpdateClassButtons();
                break;
        }

        resetKeysUpDown();
        // actually draw on the screen
        SDL_RenderPresent(gameRenderer);
        numFrames++;
    }
}

void updateAndDrawButton(Button* button) {
    updateButton(button);
    drawButton(*button);
}

void updateEverything() {
    updatePlayer();
    playerInput(SDL_GetKeyboardState(NULL));
    playerMouseInput();
    movePlayer();

    updateAllBullets();
    updateEveryEnemy(getPlayer()->position);

    updateHealthbar(getPlayer()->health, getPlayer()->class.maxHealth);

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

void drawEverything() {
    drawEveryEnemy();
    drawPlayer();
    drawAllBullets();
    drawHealthbar();
    drawHealthbarText();
    drawScore();
}