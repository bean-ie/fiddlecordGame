FILES = src/main.c src/vector.c src/bullets.c src/player.c src/enemy.c src/globals.c src/collisions.c src/healthbar.c src/textureManager.c src/button.c src/score.c src/gameState.c src/playerClass.c src/game.c src/input.c src/classSelectionMenu.c src/classAbilities.c

all:
	gcc -I SDL2/include -L SDL2/lib -o main $(FILES) -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -mwindows
	./main.exe