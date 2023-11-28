#include "headers/globals.h"
#include <stdlib.h>

double deltaTime = (double)1.0/60.0;
int screenWidth = 1600;
int screenHeight = 900;
int TARGET_FPS = 60;

int random(int max) {
	return (rand() % max);
}

int randomMinMax(int min, int max) {
    return random(max - min) + min;
}