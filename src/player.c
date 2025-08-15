#include "../include/player.h"
#include "../include/game.h"
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_scancode.h>
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

int player_shoot(Player *player, Game *game) {
   const bool *keystates = SDL_GetKeyboardState(NULL);
   if (!keystates) return 0;
   if (!keystates[SDL_SCANCODE_SPACE]) return 0;
   if (player->bullet_count>=10) return 0;
   Bullet *b = calloc(1, sizeof(Bullet));
   if (!b) return 0;
   b->x = player->x + (player->width/2) - 2.5f;
   b->y = player->y - player->height;
   SDL_FRect rect = {b->x, b->y, 5, SPRITE_HEIGHT};
   b->rect = rect;
   int c = -1;
   for (int i = 0; i < 10; i++) {
      if (player->bullets[i] == NULL) {
         c = i;
         break;
      }
   }
   if (c == -1) return 0;
   player->bullets[c] = b;
   player->bullet_count++;
   return 1;
}

int bullet_move(Bullet **b, Player *p) {
   (*b)->y -= SPRITE_HEIGHT;
   if ((*b)->y <= 0) {
      bullet_free(b);
      p->bullet_count -= 1;
      return 1;
   }
   return 1;
}

int bullet_free(Bullet **b) {
   free(*b);
   *b = NULL;
   return 1;
}
