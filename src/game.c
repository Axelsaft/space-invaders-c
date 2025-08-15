#include "../include/game.h"
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <stdio.h>
#include <SDL3/SDL.h>

const int WIDTH = 640;
const int HEIGHT = 480;

int quit(int code, Game *game) {
   if (game) {
      if (game->renderer) SDL_DestroyRenderer(game->renderer);
      if (game->window) SDL_DestroyWindow(game->window);
   }
   SDL_Quit();
   return code;
}

int init() {
   if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
      fprintf(stderr, "Failed to initialize SDL!");   
      return 0;
   }
   return 1;
}

int create_window(Game *game) {
   SDL_Window *window = SDL_CreateWindow("", WIDTH, HEIGHT, 0);
   if (!window) {
      fprintf(stderr, "Failed to create SDL Window!");
      return 0;
   }
   SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
   if (!renderer) {
      fprintf(stderr, "Failed to create SDL Renderer!");
      return 0;
   }
   game->window = window;
   game->renderer = renderer;
   return 1;
}

int new_round(Game *game) {
   return 1;
}

int game_loop(Game *game) {
  int done = 0;
  while (!done) {
      if (game->enemies_counter == 0) {
         if (!new_round(game)) return 0;
      }
   }
  return 1;
}
