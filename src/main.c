#include "../include/player.h"
#include "../include/game.h"
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <stdio.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL.h>
#include <stdlib.h>

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

   int done = 0;
   Uint64 n = SDL_GetPerformanceCounter();
   Uint64 o = SDL_GetPerformanceCounter();
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
      SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
      SDL_RenderClear(game->renderer);
      
      //*** Player ***//
      player_move(p, delta);
      player_draw(p, game);
      //*** ***//

      SDL_RenderPresent(game->renderer);
   }
   return quit(0, game);
}
