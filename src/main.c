#include "../include/game.h"
#include <stdio.h>
#include <SDL3/SDL.h>
#include <stdlib.h>

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

   int done = 0;
   while(!done) {
      SDL_Event event;
      while (SDL_PollEvent(&event)) {
         switch (event.type) {
            case SDL_EVENT_QUIT:
               done = 1;
               break;
         }
      }
      SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 0);
      SDL_RenderClear(game->renderer);
      SDL_RenderPresent(game->renderer);
   }
   return quit(0, game);
}
