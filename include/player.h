#include "game.h"
#include <SDL3/SDL_render.h>
#ifndef PLAYER_H

typedef struct {
   float x, y;
   float speed;
   SDL_Texture *texture;
   float width, height;
} Player;

int player_create(Player **, Game *);

int player_init(Player *);

int player_draw(Player *, Game *);

int player_free(Player *);

int player_move(Player *, double delta);

#endif
