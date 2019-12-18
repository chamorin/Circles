#include "player.h"
#include "sdl2.h"
#include "spritesheet.h"

#include <stdbool.h>

struct Player *Player_initialize(SDL_Renderer *renderer) {
  struct Player *player;
  player = malloc(sizeof(struct Player));
  player->renderer = renderer;
  player->state = PLAYER_ALIVE;
  player->player_sprite =
      Spritesheet_create(PLAYER_FILENAME, 1, 1, 1, renderer);
  return player;
}

int Player_alpha(bool chosen) { return chosen ? 255 : 64; }

void Player_run(struct Player *player) {
  SDL_Event e;
  while (player->state != PLAYER_DEAD) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_LEFT:
          printf("LEFT\n");
          break;
        case SDLK_RIGHT:
          printf("RIGHT\n");
          break;
        }
      }
    }
    SDL_SetRenderDrawColor(player->renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(player->renderer);
    Spritesheet_render(player->player_sprite, BACKGROUND_X, BACKGROUND_Y, 255,
                       0);
    SDL_RenderPresent(player->renderer);
  }
}

void Player_delete(struct Player *player) {
  if (player != NULL) {
    Spritesheet_delete(player->player_sprite);
    free(player);
  }
}

void Player_move(struct Player *player) {

}
