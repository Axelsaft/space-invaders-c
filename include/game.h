#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>

#ifndef GAME_H
#define GAME_H

extern const int WIDTH;
extern const int HEIGHT;

typedef struct {
   int x;
   int y;
   SDL_Texture *texture;
} Enemie;

typedef struct {
   SDL_Window *window;
   SDL_Renderer *renderer;
   int round;
   int enemies_counter;
   Enemie enemies[64];
} Game;

int quit(int, Game *);

int init();

int create_window(Game *);

int new_round(Game *);

int game_loop(Game *);

#endif
