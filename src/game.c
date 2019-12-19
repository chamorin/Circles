#include "game.h"
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
  game->player_sprite = Spritesheet_create(PLAYER_FILENAME, 1, 1, 1, renderer);
  game->background = Spritesheet_create(BACKGROUND_FILENAME, 1, 1, 1, renderer);
  return game;
}

int Game_alpha(bool chosen) { return chosen ? 255 : 64; }

void Game_run(struct Game *game) {
  SDL_Event e;
  float angle = PLAYER_MOVEMENT_ANGLE;
  float originX = SCREEN_WIDTH / 2;
  float originY = SCREEN_HEIGHT / 2;

  game->player_sprite_posX =
      (originX + cos(angle) * CENTER_CIRCLE_RADIUS) - PLAYER_WIDTH / 2;
  game->player_sprite_posY =
      (originY + sin(angle) * CENTER_CIRCLE_RADIUS) - PLAYER_HEIGHT / 2;

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
    SDL_Point point;
    point.x = originX;
    point.y = originY;
    SDL_Color color = {128, 128, 128};
    Spritesheet_render(game->background, BACKGROUND_X, BACKGROUND_Y, 255, 0);
    Game_drawCircle(point, game->renderer, CENTER_CIRCLE_RADIUS - 20, color);
    Spritesheet_render(game->player_sprite, game->player_sprite_posX,
                       game->player_sprite_posY, 255, 0);
    SDL_RenderPresent(game->renderer);
  }
}

void Game_delete(struct Game *game) {
  if (game != NULL) {
    Spritesheet_delete(game->background);
    Spritesheet_delete(game->player_sprite);
    free(game);
  }
}

void Player_move_right(struct Game *game, const float *originX,
                       const float *originY, float *angle) {
  *angle += PLAYER_MOVEMENT_ANGLE;
  game->player_sprite_posX =
      (*originX + cos(*angle) * CENTER_CIRCLE_RADIUS) - PLAYER_WIDTH / 2;
  game->player_sprite_posY =
      (*originY + sin(*angle) * CENTER_CIRCLE_RADIUS) - PLAYER_HEIGHT / 2;
  if (game->player_position == PLAYER_POSSIBLE_POSITIONS - 1) {
    game->player_position = 0;
  } else {
    ++game->player_position;
  }
}

void Player_move_left(struct Game *game, const float *originX,
                      const float *originY, float *angle) {
  *angle -= PLAYER_MOVEMENT_ANGLE;
  game->player_sprite_posX =
      (*originX + cos(*angle) * CENTER_CIRCLE_RADIUS) - PLAYER_WIDTH / 2;
  game->player_sprite_posY =
      (*originY + sin(*angle) * CENTER_CIRCLE_RADIUS) - PLAYER_HEIGHT / 2;
  if (game->player_position == 0) {
    game->player_position = PLAYER_POSSIBLE_POSITIONS - 1;
  } else {
    --game->player_position;
  }
}

void Game_drawCircle(SDL_Point center, SDL_Renderer *renderer, int radius,
                     SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  for (int w = 0; w < radius * 2; ++w) {
    for (int h = 0; h < radius * 2; ++h) {
      int dx = radius - w;
      int dy = radius - h;
      if ((dx * dx + dy * dy) <= (radius * radius)) {
        SDL_RenderDrawPoint(renderer, center.x + dx, center.y + dy);
      }
    }
  }
}