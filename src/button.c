#include "headers/button.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "headers/textureManager.h"
#include "headers/gameState.h"
#include "headers/globals.h"
#include "headers/input.h"
#include "headers/classSelectionMenu.h"

SDL_Rect buttonRect, buttonTextRect;
SDL_Texture* buttonSprite;
TTF_Font* buttonFont;
SDL_Color buttonTextColor;

void setupButtons() {
    buttonSprite = createTexture("content/sprites/buttonBack.png");
    buttonFont = TTF_OpenFont("content/fonts/Square.ttf", 48);
    buttonTextColor.r = 255;
    buttonTextColor.g = 255;
    buttonTextColor.b = 255;
}

Button createButton(Vector2 position, Vector2 size, char* text, int id) {
    Button button;
    button.position = position;
    button.size = size;
    button.text = text;
    button.id = id;
    button.pressed = 0;
    return button;
}

int mouseX, mouseY;
Uint32 mouseState;
void updateButton(Button* button) {
    if (getMousePosition().x >= button->position.x &&
        getMousePosition().x <= button->position.x + button->size.x &&
        getMousePosition().y >= button->position.y  &&
        getMousePosition().y <= button->position.y + button->size.y) {
            if (getMouseButtonDown(1) && button->pressed == 0) {
                button->pressed = 1;
            }
            if (getMouseButtonUp(1) && button->pressed == 1) {
                buttonClick(button->id);
                button->pressed = 0;
            }
        }

    if (button->pressed == 1 && !getMouseButton(1)) {
        button->pressed = 0;
    }
}

void drawButton(Button button) {
    buttonRect.x = button.position.x + (button.pressed ? button.size.x * 0.1 * 0.5 : 0);
    buttonRect.y = button.position.y + (button.pressed ? button.size.y * 0.1 * 0.5 : 0);
    buttonRect.w = button.size.x * (button.pressed ? 0.9 : 1);
    buttonRect.h = button.size.y * (button.pressed ? 0.9 : 1);
    Text text = createText(buttonFont, button.text, buttonTextColor);
    buttonTextRect.x = buttonRect.x + buttonRect.w/2 - text.w/2 + (button.pressed ? text.w * 0.1 * 0.5 : 0);
    buttonTextRect.y = buttonRect.y + buttonRect.h/2 - text.h/2 + (button.pressed ? text.h * 0.1 * 0.5 : 0);
    buttonTextRect.w = text.w * (button.pressed ? 0.9 : 1);
    buttonTextRect.h = text.h * (button.pressed ? 0.9 : 1);
    render(buttonSprite, &buttonRect);
    render(text.texture, &buttonTextRect);
    SDL_DestroyTexture(text.texture);
}

void buttonClick(int id) {
    switch (id) {
        case 0:
            setGameState(CharacterSelection);
            break;
        case 1:
            setGameState(Menu);
            break;
        case 2:
            setGameState(Running);
            break;
        case 10:
            chooseClass(0);
            setGameState(Running);
            break;
        case 11:
            chooseClass(1);
            setGameState(Running);
            break;
        case 12:
            chooseClass(2);
            setGameState(Running);
            break;
        case 13:
            chooseClass(3);
            setGameState(Running);
            break;
        case 14:
            chooseClass(4);
            setGameState(Running);
            break;
    }
}