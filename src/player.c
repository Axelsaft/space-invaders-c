#include "../include/player.h"
#include "../include/game.h"
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <stdlib.h>

#define DIRECTION_LEFT -1;
#define DIRECTION_RIGHT 1;

int player_create(Player **player, Game *game) {
   *player = calloc(1, sizeof(Player));
   if (!*player) return 0;
   
   SDL_Surface *surface = SDL_LoadBMP("./ressources/spaceship.bmp");
   if (!surface) return 0;
   SDL_Texture *texture = SDL_CreateTextureFromSurface(game->renderer, surface);
   if (!texture) return 0;
   SDL_SetTextureScaleMode(texture,SDL_SCALEMODE_NEAREST);
   (*player)->texture = texture;
   return 1;
}

int player_init(Player *player) {
   player->height = SPRITE_WIDTH;
   player->width = SPRITE_HEIGHT;
   
   player->x = ((float)WIDTH / 2) - (player->width/2);
   player->y = (float)HEIGHT - (player->height + (player->height/2));

   player->speed = 0.5f;

   return 1;
}

int player_draw(Player *player, Game *game) {
   SDL_FRect destination = {player->x, player->y, player->width, player->height};
   SDL_RenderTexture(game->renderer, player->texture, NULL, &destination);
   return 1;
}

int player_free(Player *player) {
   free(player->texture);
   free(player);
   return 1;
}

int player_move(Player *player, double delta) {
   const bool *keystates = SDL_GetKeyboardState(NULL);
   float direction_x = 0; // I am using this to stop moving if the user presses a and d together 
   if (!keystates) return 0;
   if (keystates[SDL_SCANCODE_A]) {
      direction_x += DIRECTION_LEFT;
   } 
   if (keystates[SDL_SCANCODE_D]) { 
      direction_x += DIRECTION_RIGHT;
   }

   player->x += (player->speed * delta) * direction_x;

   // If too far on the left
   if (player->x < 0) {
      player->x = 0;
   }
   // If too far on the right
   if ((player->x + player->width) > WIDTH) {
      player->x = WIDTH - player->width;
   }
   return 1;
}
