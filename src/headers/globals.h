#ifndef GLOBALS_H
#define GLOBALS_H

extern double deltaTime;

extern int screenWidth;
extern int screenHeight;

extern int TARGET_FPS;

int random(int max);
int randomMinMax(int min, int max);

enum GameState {
    Menu,
    Paused,
    Running,
    CharacterSelection
};

#endif