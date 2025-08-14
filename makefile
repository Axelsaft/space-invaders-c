program: main game
	gcc -lSDL3 -o bin/space-invaders build/main.o build/game.o

main: src/main.c include/game.h
	gcc -c src/main.c -o build/main.o
	
game: src/game.c include/game.h
	gcc -c src/game.c -o build/game.o
