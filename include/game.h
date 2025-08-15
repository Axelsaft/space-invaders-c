#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>

extern const int WIDTH;
extern const int HEIGHT;
extern const int SPRITE_WIDTH;
extern const int SPRITE_HEIGHT;

typedef struct Enemy Enemy;

typedef struct Player Player;

typedef struct Game {
   SDL_Window *window;
   SDL_Renderer *renderer;
   int round;
   int enemies_counter;
   Enemy *enemies[64];
   int direction;
} Game;

int quit(int, Game *);

int init();

int create_window(Game *);

int new_round(Game *);

int game_loop(Game *);

int game_move_enemies(Game *);
