#include "player.h"
#include "sdl2.h"
#include "spritesheet.h"

#include <math.h>
#include <stdbool.h>

struct Player *Player_initialize(SDL_Renderer *renderer) {
  struct Player *player;
  player = malloc(sizeof(struct Player));
  player->renderer = renderer;
  player->state = PLAYER_ALIVE;
  player->position = 0;
  player->player_sprite =
      Spritesheet_create(PLAYER_FILENAME, 1, 1, 1, renderer);
  return player;
}

int Player_alpha(bool chosen) { return chosen ? 255 : 64; }

void Player_run(struct Player *player) {
  SDL_Event e;
  float angle = PLAYER_MOVEMENT_ANGLE;
  float originX = SCREEN_WIDTH / 2;
  float originY = SCREEN_HEIGHT / 2;

  player->sprite_posX = originX + cos(angle) * CENTER_CIRCLE_RADIUS;
  player->sprite_posY = originY + sin(angle) * CENTER_CIRCLE_RADIUS;

  while (player->state != PLAYER_DEAD) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_RIGHT:
          Player_move_right(player, &originX, &originY, &angle);
          break;
        case SDLK_LEFT:
          Player_move_left(player, &originX, &originY, &angle);
          break;
        }
      }
    }
    SDL_SetRenderDrawColor(player->renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(player->renderer);
    Spritesheet_render(player->player_sprite, player->sprite_posX,
                       player->sprite_posY, 255, 0);
    SDL_RenderPresent(player->renderer);
  }
}

void Player_delete(struct Player *player) {
  if (player != NULL) {
    Spritesheet_delete(player->player_sprite);
    free(player);
  }
}

void Player_move_right(struct Player *player, const float *originX,
                       const float *originY, float *angle) {
  *angle += PLAYER_MOVEMENT_ANGLE;
  player->sprite_posX = *originX + cos(*angle) * CENTER_CIRCLE_RADIUS;
  player->sprite_posY = *originY + sin(*angle) * CENTER_CIRCLE_RADIUS;
}

void Player_move_left(struct Player *player, const float *originX,
                      const float *originY, float *angle) {
  *angle -= PLAYER_MOVEMENT_ANGLE;
  player->sprite_posX = *originX + cos(*angle) * CENTER_CIRCLE_RADIUS;
  player->sprite_posY = *originY + sin(*angle) * CENTER_CIRCLE_RADIUS;
}