all:
	gcc -I SDL2/include -L SDL2/lib -o main src/main.c src/vector.c src/bullets.c src/player.c src/enemy.c src/globals.c src/collisions.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
	./main.exe