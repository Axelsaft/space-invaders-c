#pragma once
#include <SDL3/SDL_render.h>

typedef struct Game Game;

typedef struct Enemy {
   float x, y;
   SDL_Texture *texture;
   float width, height;
} Enemy;

int enemy_create(Enemy **, Game *);

int enemy_init(Enemy *, int c);

int enemy_draw(Enemy *, Game *);

int enemy_free(Enemy *);

