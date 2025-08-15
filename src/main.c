#include "../include/game.h"
#include "../include/player.h"
#include "../include/enemy.h"
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <stdio.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL.h>
#include <stdlib.h>

const int SPRITE_SIZE = 30;

double get_delta(Uint64 *n, Uint64 *o) {
   *o = *n;
   *n = SDL_GetPerformanceCounter();
   return (double)((*n - *o) * 1000 / (double)SDL_GetPerformanceFrequency()); 
}

int main() {
   if (!init()) {
      return quit(-1, NULL);
   }

   Game *game = calloc(1, sizeof(Game));
   if (!game) {
      fprintf(stderr, "Failed to create game struct!");
      return quit(-1, NULL);
   }
   if (!create_window(game)) {
      return quit(-1, game);
   }
   
   Player* p;
   if(!player_create(&p, game)){
      fprintf(stderr, "Error creating player structure!");
      return quit(-1, game);
   }
   player_init(p);

   float move_timer = 0;
   float bullet_shoot_timer = 0;
   float bullet_move_timer = 0;

   int done = 0;
   Uint64 n = SDL_GetPerformanceCounter();
   Uint64 o = SDL_GetPerformanceCounter();
   
   game->round = 4;
   while(!done) {
      double delta = get_delta(&n, &o);
      SDL_Event event;
      while (SDL_PollEvent(&event)) {
         switch (event.type) {
            case SDL_EVENT_QUIT:
               done = 1;
               break;
         }
      }

      //*** Timers ***//
      if (game->enemies_counter == 0) {
         new_round(game);
      }

      if (move_timer > 0 && move_timer >= 60){
         move_timer = 0;
         game_move_enemies(game);
      }
      move_timer += 0.1 * delta;

      if (bullet_shoot_timer > 0) {
         bullet_shoot_timer -= 0.1 * delta;
      }

      if (bullet_move_timer <= 0) {
         bullet_move_timer = 10;
         for (int i = 0; i < 10; i++) {
            Bullet *b = p->bullets[i];
            if (b == NULL) continue;
            bullet_move(&p->bullets[i], p);
         }
      }
      bullet_move_timer -= 0.1 * delta;
      //*** ***//
 
      //*** Rendering ***//
      SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
      SDL_RenderClear(game->renderer);
      //* Player *//
      player_move(p, delta);
      if (bullet_shoot_timer <= 0 && player_shoot(p, game)) {
         bullet_shoot_timer = 30;
      }
      player_draw(p, game);
      //* *//

      //* Enemy *//
      for (int i = 0; i < 64; i++) {
         if(game->enemies[i] == NULL) continue;
         enemy_draw(game->enemies[i], game);
      }
      for (int i = 0; i < 10; i++) {
         Bullet *b = p->bullets[i];
         if (!b) continue;
         b->rect.x = b->x;
         b->rect.y = b->y;
         SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
         SDL_RenderFillRect(game->renderer, &b->rect);
      }
      //* *//
      //*** ***//
      SDL_RenderPresent(game->renderer);
   }
   return quit(0, game);
}
