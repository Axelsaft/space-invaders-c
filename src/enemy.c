#include "../include/enemy.h"
#include "../include/game.h"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <math.h>
#include <stdlib.h>

int enemy_create(Enemy ** enemy, Game *game) {
   *enemy = calloc(1, sizeof(Enemy));
   if (!*enemy) return 0;
   SDL_Surface *surface = SDL_LoadBMP("./ressources/enemy.bmp");
   if (!surface) return 0;
   SDL_Texture *texture = SDL_CreateTextureFromSurface(game->renderer, surface);
   if (!texture) return 0;
   SDL_SetTextureScaleMode(texture,SDL_SCALEMODE_NEAREST);
   (*enemy)->texture = texture;
   return 1;
}

int enemy_init(Enemy *enemy, int c) {
   enemy->width = SPRITE_WIDTH;
   enemy->height = SPRITE_HEIGHT;

   int max_c = (WIDTH / enemy->width)-1;
   int row = (int)floor((double)c / (double)max_c);
   c = c - (max_c * row);

   float remainder = WIDTH % (int)enemy->width;
   if (remainder > 0) {
      remainder /= 2;
   }
   enemy->x = (enemy->width * c) + remainder;
   enemy->y = (enemy->height * row);

   return 1;
}

int enemy_draw(Enemy *enemy, Game *game) {
   SDL_FRect rect = {enemy->x, enemy->y, enemy->width, enemy->height};
   SDL_RenderTexture(game->renderer, enemy->texture, NULL, &rect);
   return 1;
}

int enemy_free(Enemy *enemy) {
   free(enemy->texture);
   free(enemy);
   return 1;
}
