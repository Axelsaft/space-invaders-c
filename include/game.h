#include <SDL3/SDL.h>

#ifndef GAME_H
#define GAME_H

extern const int WIDTH;
extern const int HEIGHT;

typedef struct {
   SDL_Window *window;
   SDL_Renderer *renderer;
} Game;

int quit(int, Game *);

int init();

int create_window(Game *);

#endif
