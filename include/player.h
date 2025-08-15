#pragma once
#include "game.h"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

typedef struct Game Game;

typedef struct Bullet {
   float x,y;
   SDL_FRect rect;
} Bullet;

typedef struct Player {
   float x, y;
   float speed;
   SDL_Texture *texture;
   float width, height;
   int bullet_count;
   Bullet *bullets[10];
} Player;

int player_create(Player **, Game *);

int player_init(Player *);

int player_draw(Player *, Game *);

int player_free(Player *);

int player_move(Player *, double delta);

int player_shoot(Player *, Game *);

int bullet_move(Bullet **, Player *);

int bullet_free(Bullet **);
