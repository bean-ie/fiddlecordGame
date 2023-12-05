#include "headers/button.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "headers/textureManager.h"
#include "headers/gameState.h"

SDL_Rect buttonRect, buttonTextRect;
SDL_Texture* buttonSprite;
TTF_Font* buttonFont;
SDL_Color buttonTextColor;

void setupButtons(SDL_Renderer* renderer) {
    buttonSprite = createTexture("content/sprites/buttonBack.png", renderer);
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
    return button;
}

int mouseX, mouseY;
Uint32 mouseState;
void updateButton(Button button) {
    mouseState = SDL_GetMouseState(&mouseX, &mouseY);
    if (mouseX >= button.position.x &&
        mouseX <= button.position.x + button.size.x &&
        mouseY >= button.position.y  &&
        mouseY <= button.position.y + button.size.y) {
            if (SDL_BUTTON(1) & mouseState == SDL_BUTTON(1))
                buttonClick(button.id);
        }
}

void drawButton(Button button, SDL_Renderer* renderer) {
    buttonRect.x = button.position.x;
    buttonRect.y = button.position.y;
    buttonRect.w = button.size.x;
    buttonRect.h = button.size.y;
    Text text = createText(buttonFont, button.text, buttonTextColor, renderer);
    buttonTextRect.x = buttonRect.x + buttonRect.w/2 - text.w/2;
    buttonTextRect.y = buttonRect.y + buttonRect.h/2 - text.h/2;
    buttonTextRect.w = text.w;
    buttonTextRect.h = text.h;
    if (SDL_RenderCopy(renderer, buttonSprite, NULL, &buttonRect) != 0) {
        printf("%s", SDL_GetError());
    }
    SDL_RenderCopy(renderer, text.texture, NULL, &buttonTextRect);
}

void buttonClick(int id) {
    switch (id) {
        case 0:
            setGameState(2);
            break;
        case 1:
            setGameState(0);
            break;
        case 2:
            setGameState(2);
            break;
    }
}