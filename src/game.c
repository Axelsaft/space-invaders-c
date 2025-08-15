#include "../include/enemy.h"
#include "../include/game.h"
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <stdio.h>
#include <SDL3/SDL.h>

const int WIDTH = 640;
const int HEIGHT = 480;
const int SPRITE_WIDTH = 40;
const int SPRITE_HEIGHT = 40;

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
   game->direction = 1;
   game->window = window;
   game->renderer = renderer;
   return 1;
}

int new_round(Game *game) {
   game->enemies_counter = 0;
   game->round++;
   for (int i = 0; i < game->round; i++) {
      if (i > 63) break;
      Enemy *e;
      if (!enemy_create(&e, game)) {
         fprintf(stderr, "new_round | failed to create enemy!");
         return 0;
      }
      enemy_init(e, i);
      game->enemies[i] = e;
      game->enemies_counter++;
   }
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

int game_move_enemies(Game *game) {
   if (game->enemies_counter == 0) return 0;
   printf("Test");
   int c = game->enemies_counter-1;
   Enemy *e;
   float new_pos;
   if (game->direction > 0) {
      for (int i = 63; i >= 0; i--) {
         if (game->enemies[i] != NULL) {
            e = game->enemies[i];
         }
      }
   } else {
      for (int i = 0; i < 64; i++) {
         if (game->enemies[i] != NULL) {
            e = game->enemies[i];
         }
      }
   }
   new_pos = e->x + (e->width * game->direction);
   if (new_pos < 0 || new_pos+e->width > WIDTH) {
      game->direction *= -1;
      for (int i = 0; i<64; i++) {
         e = game->enemies[i];
         if (e != NULL) {
            e->y += e->height;
         }
      }
   } else {
      for (int i = 0; i<64; i++) {
         e = game->enemies[i];
         e->x += e->width * game->direction;
      }
   }
   return 1;
}
