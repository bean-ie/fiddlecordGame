#include "headers/classAbilities.h"
#include "headers/player.h"
#include "headers/playerClass.h"
#include "headers/score.h"
#include "headers/textureManager.h"
#include "headers/globals.h"
#include "headers/input.h"
#include "SDL2/SDL.h"
#include <math.h>

int ryanAmmoCount = 5;

int esmileSwordRotation = 0;
int esmileClickDesiredRotation;
int esmileAttacking = 0;
int esmileSwordSwingAmount = 60;
SDL_Rect esmileSwordRect;
SDL_Texture* esmileSwordTexture;

void setupClassAbilities() {
    esmileSwordTexture = createTexture("content/sprites/characters/esmileSword.png");
    esmileSwordRotation = 0;
    esmileSwordRect.w = 598/3;
    esmileSwordRect.h = 574/3;
}

float bezierBlend(float t)
{
    return t * t * (3.0f - 2.0f * t);
}

float bezier(float a, float b, float t)
{
	return a + (b - a) * bezierBlend(t);
}

int onShootAbility() {
    switch (getPlayer()->class.id) {

        case 2:
            return 1;
            Vector2 playerPos = {};
            playerPos.x = getPlayer()->position.x + getPlayer()->class.size.x/2.0;
            playerPos.y = getPlayer()->position.y + getPlayer()->class.size.y/2.0;
            esmileClickDesiredRotation = atan((getMousePosition().y - playerPos.y) / (getMousePosition().x - playerPos.x)) * 180.0/3.1415926 + 44;
            if (getMousePosition().x - playerPos.x <= 0) {
                esmileClickDesiredRotation += 180;
            }
            esmileAttacking = 1;
            return 0;
        break;
        
        case 3:
            if (getPlayer()->class.bulletsPerShot != floor(getScore() / 50.0) + 2) {
                getPlayer()->class.bulletsPerShot = floor(getScore() / 50.0) + 2;
                getPlayer()->class.reloadTime = floor(getScore() / 50.0) * 0.11 + 0.4;
                if (getScore() >= 100) getPlayer()->class.damage = 60.0 * 0.8;
            }
            if (getPlayer()->class.bulletSpreadAngle != floor(getScore() / 4.0) * 1 + 10) {
                getPlayer()->class.bulletSpreadAngle = floor(getScore() / 4.0) * 1 + 10;
            }
        break;

        case 4:
            if (ryanAmmoCount > 0) {
                ryanAmmoCount--;
                return 1;
            } else {
                return 0;
            }
        break;
    }
    return 1;
}

double esmilet = 0;
void abilityLoop() {
    switch (getPlayer()->class.id) {
        
        case 2:
            if (esmileAttacking == 0) return;

            esmileSwordRotation = bezier(esmileClickDesiredRotation - esmileSwordSwingAmount, esmileClickDesiredRotation + esmileSwordSwingAmount, esmilet);
            esmilet += deltaTime * 3;
            if (esmilet >= 1) {
                esmileAttacking = 0;
                esmilet = 0;
            }
            Vector2 swordOffset = {};
            swordOffset = rotateVector((Vector2){125,0}, -esmileSwordRotation+44);
            esmileSwordRect.x = getPlayer()->position.x + getPlayer()->class.size.x/2.0 + swordOffset.x;
            esmileSwordRect.y = getPlayer()->position.y + getPlayer()->class.size.y/2.0 - esmileSwordRect.h - swordOffset.y;
            SDL_Point center = {};
            center.x = 0;
            center.y = esmileSwordRect.h;
            renderEx(esmileSwordTexture, &esmileSwordRect, esmileSwordRotation, &center);
        break;

    }
}

void ryanReplenishAmmo(int full) {
    if (full == 0){
        ryanAmmoCount +=1;
    } else {
        ryanAmmoCount = 5;
    }
}