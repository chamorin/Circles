#include "game.h"
#include "SDL2_gfxPrimitives.h"
#include "sdl2.h"
#include "spritesheet.h"

#include <math.h>
#include <stdbool.h>

struct Game *Game_initialize(SDL_Renderer *renderer) {
  struct Game *game;
  game = malloc(sizeof(struct Game));
  game->renderer = renderer;
  game->state = GAME_PLAY;
  game->player_position = 0;
  return game;
}

int Game_alpha(bool chosen) { return chosen ? 255 : 64; }

void Game_run(struct Game *game) {
  SDL_Event e;
  float angle = SECTOR_ANGLE + SECTOR_ANGLE / 2;
  float sector_angle = CIRCLE_TO_RADIANT;
  float originX = SCREEN_WIDTH / 2;
  float originY = SCREEN_HEIGHT / 2;
  int rotation = 0;

  game->player_triang_posX = (originX + cos(angle) * CENTER_CIRCLE_RADIUS);
  game->player_triang_posY = (originY + sin(angle) * CENTER_CIRCLE_RADIUS);

  while (game->state != GAME_OVER) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_RIGHT:
          Player_move_right(game, &originX, &originY, &angle);
          break;
        case SDLK_LEFT:
          Player_move_left(game, &originX, &originY, &angle);
          break;
        }
      }
    }
    SDL_SetRenderDrawColor(game->renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(game->renderer);

    Game_drawBackground(game->renderer, &originX, &originY, &rotation);
    //++rotation;

    filledCircleRGBA(game->renderer, originX, originY,
                     CENTER_CIRCLE_RADIUS - 20, 128, 128, 128, 255);

    Player_drawTrigon(game->renderer, &game->player_triang_posX,
                      &game->player_triang_posY, &originX, &originY, &angle,
                      &rotation);

    SDL_RenderPresent(game->renderer);
  }
}

void Game_delete(struct Game *game) {
  if (game != NULL) {
    free(game);
  }
}

void Player_drawTrigon(SDL_Renderer *renderer, const float *player_triang_posX,
                       const float *player_triang_posY, const float *originX,
                       const float *originY, float *angle,
                       const int *rotation) {

  float left_point_X =
      *originX + cos(*angle - 0.3) * (CENTER_CIRCLE_RADIUS - 10);
  float left_point_Y =
      *originY + sin(*angle - 0.3) * (CENTER_CIRCLE_RADIUS - 10);
  float right_point_X =
      *originX + cos(*angle + 0.3) * (CENTER_CIRCLE_RADIUS - 10);
  float right_point_Y =
      *originY + sin(*angle + 0.3) * (CENTER_CIRCLE_RADIUS - 10);

  filledTrigonRGBA(renderer, left_point_X, left_point_Y, *player_triang_posX,
                   *player_triang_posY, right_point_X, right_point_Y, 0, 0, 255,
                   255);
}

void Player_move_right(struct Game *game, const float *originX,
                       const float *originY, float *angle) {
  *angle += SECTOR_ANGLE;
  game->player_triang_posX = (*originX + cos(*angle) * CENTER_CIRCLE_RADIUS);
  game->player_triang_posY = (*originY + sin(*angle) * CENTER_CIRCLE_RADIUS);
  if (game->player_position == PLAYER_POSSIBLE_POSITIONS - 1) {
    game->player_position = 0;
  } else {
    ++game->player_position;
  }
}

void Player_move_left(struct Game *game, const float *originX,
                      const float *originY, float *angle) {
  *angle -= SECTOR_ANGLE;
  game->player_triang_posX = (*originX + cos(*angle) * CENTER_CIRCLE_RADIUS);
  game->player_triang_posY = (*originY + sin(*angle) * CENTER_CIRCLE_RADIUS);
  if (game->player_position == 0) {
    game->player_position = PLAYER_POSSIBLE_POSITIONS - 1;
  } else {
    --game->player_position;
  }
}

void Game_drawBackground(SDL_Renderer *renderer, const float *originX,
                         const float *originY, const int *rotation) {
  filledPieRGBA(renderer, *originX, *originY, SCREEN_WIDTH, 0 + *rotation,
                60 + *rotation, 204, 204, 204, 255);
  filledPieRGBA(renderer, *originX, *originY, SCREEN_WIDTH, 60 + *rotation,
                120 + *rotation, 255, 255, 255, 255);
  filledPieRGBA(renderer, *originX, *originY, SCREEN_WIDTH, 120 + *rotation,
                180 + *rotation, 204, 204, 204, 255);
  filledPieRGBA(renderer, *originX, *originY, SCREEN_WIDTH, 180 + *rotation,
                240 + *rotation, 255, 255, 255, 255);
  filledPieRGBA(renderer, *originX, *originY, SCREEN_WIDTH, 240 + *rotation,
                300 + *rotation, 204, 204, 204, 255);
  filledPieRGBA(renderer, *originX, *originY, SCREEN_WIDTH, 300 + *rotation,
                360 + *rotation, 255, 255, 255, 255);
}
