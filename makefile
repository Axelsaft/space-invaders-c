program: main game player enemy
	rm -rf ./bin/ressources
	cp -r ./ressources ./bin/ressources
	gcc -lSDL3 -lm -g -o bin/space-invaders build/main.o build/game.o build/player.o build/enemy.o
	cd ./bin && ./space-invaders

main: src/main.c include/game.h
	gcc -g -c src/main.c -o build/main.o
	
game: src/game.c include/game.h
	gcc -g -c src/game.c -o build/game.o

player: src/player.c include/player.h
	gcc -g -c src/player.c -o build/player.o

enemy: src/enemy.c include/enemy.h
	gcc -g -c src/enemy.c -o build/enemy.o
