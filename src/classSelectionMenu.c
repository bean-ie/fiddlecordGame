#include "headers/classSelectionMenu.h"
#include "headers/playerClass.h"
#include "headers/vector.h"
#include "headers/textureManager.h"
#include "headers/game.h"
#include "headers/button.h"
#include <math.h>

PlayerClass classes[5];
Button buttons[5];
Text nameTexts[5];
TTF_Font* nameFont;

void createClasses() {
    nameFont = TTF_OpenFont("content/fonts/Square.ttf", 36);
    SDL_Color nameTextColor = {0, 0, 0};

    PlayerClass class;

    class.name = "Beanie";
    class.bulletsPerShot = 1;
    class.bulletSpreadAngle = 5;
    class.damage = 100;
    class.reloadTime = 0.35;
    class.mass = 1;
    class.maxHealth = 100;
    class.shotKnockbackForce = 250;
    class.size = (Vector2){100, 100};
    class.sprite = createTexture("content/sprites/characters/beanie.png");
    classes[0] = class;
    buttons[0] = createButton((Vector2){250 + (400 * (0 % 4)), 175 + (300 * 0)}, (Vector2){150, 60}, "play", 10);
    nameTexts[0] = createText(nameFont, class.name, nameTextColor);

    class.name = "Fapas";
    class.bulletsPerShot = 10;
    class.bulletSpreadAngle = 20;
    class.damage = 25;
    class.reloadTime = 0.7;
    class.mass = 0.6;
    class.maxHealth = 50;
    class.shotKnockbackForce = 5000;
    class.size = (Vector2){75, 75};
    class.sprite = createTexture("content/sprites/characters/fapas.png");
    classes[1] = class;
    buttons[1] = createButton((Vector2){250 + (400 * (1 % 4)), 175 + (300 * 0)}, (Vector2){150, 60}, "play", 11);
    nameTexts[1] = createText(nameFont, class.name, nameTextColor);

    class.name = "Esmile";
    class.bulletsPerShot = 1;
    class.bulletSpreadAngle = 5;
    class.damage = 400;
    class.reloadTime = 1.25;
    class.mass = 2;
    class.maxHealth = 250;
    class.shotKnockbackForce = 7500;
    class.size = (Vector2){125, 125};
    class.sprite = createTexture("content/sprites/characters/esmile.png");
    classes[2] = class;
    buttons[2] = createButton((Vector2){250 + (400 * (2 % 4)), 175 + (300 * 0)}, (Vector2){150, 60}, "play", 12);
    nameTexts[2] = createText(nameFont, class.name, nameTextColor);

    class.name = "Fortuna";
    class.bulletsPerShot = 2;
    class.bulletSpreadAngle = 20;
    class.damage = 60;
    class.reloadTime = 0.5;
    class.mass = 0.85;
    class.maxHealth = 175;
    class.shotKnockbackForce = 500;
    class.size = (Vector2){85, 85};
    class.sprite = createTexture("content/sprites/characters/fortuna.png");
    classes[3] = class;
    buttons[3] = createButton((Vector2){250 + (400 * (3 % 4)), 175 + (300 * 0)}, (Vector2){150, 60}, "play", 13);
    nameTexts[3] = createText(nameFont, class.name, nameTextColor);

    class.name = "Ryorthios";
    class.bulletsPerShot = 1;
    class.bulletSpreadAngle = 25;
    class.damage = 14;
    class.reloadTime = 0.05;
    class.mass = 1;
    class.maxHealth = 85;
    class.shotKnockbackForce = 100;
    class.size = (Vector2){100, 100};
    class.sprite = createTexture("content/sprites/characters/ryan.png");
    classes[4] = class;
    buttons[4] = createButton((Vector2){250 + (400 * (4 % 4)), 175 + (300 * 1)}, (Vector2){150, 60}, "play", 14);
    nameTexts[4] = createText(nameFont, class.name, nameTextColor);
}

SDL_Rect nameTextRect = {};
SDL_Rect classImageRect = {};

void renderAndUpdateClassButtons() {
    int i;
    for (i = 0; i < 5; i++) {
        classImageRect.w = 200;
        classImageRect.h = 200;
        classImageRect.x = (20 + (400 * (i % 4)));
        classImageRect.y = (50 + (300 * (floor(i / 4.0))));
        render(classes[i].sprite, &classImageRect);

        nameTextRect.w = nameTexts[i].w;
        nameTextRect.h = nameTexts[i].h;
        nameTextRect.x = (325 + (400 * (i % 4))) - nameTextRect.w/2;
        nameTextRect.y = (90 + (300 * (floor(i / 4.0))));
        render(nameTexts[i].texture, &nameTextRect);

        updateButton(&buttons[i]);
        drawButton(buttons[i]);
    }
}

void chooseClass(int index) {
    selectClass(classes[index]);
}