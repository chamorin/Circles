#include "game.h"
#include "SDL2_gfxPrimitives.h"
#include "sdl2.h"
#include "spritesheet.h"

#include <math.h>
#include <stdbool.h>
#include <time.h>

struct Game *Game_initialize(SDL_Renderer *renderer) {
  struct Game *game;
  game = malloc(sizeof(struct Game));
  game->renderer = renderer;
  game->state = GAME_PLAY;
  game->player_position = 1;
  game->first_digit_sprite =
      Spritesheet_create(CHRONO_FILENAME, 1, 11, 11, renderer);
  game->second_digit_sprite =
      Spritesheet_create(CHRONO_FILENAME, 1, 11, 11, renderer);
  game->dot_sprite = Spritesheet_create(CHRONO_FILENAME, 1, 11, 11, renderer);
  game->third_digit_sprite =
      Spritesheet_create(CHRONO_FILENAME, 1, 11, 11, renderer);
  return game;
}

void Game_run(struct Game *game) {
  SDL_Event e;
  float angle = SECTOR_ANGLE_RADIANT + SECTOR_ANGLE_RADIANT / 2;
  float originX = SCREEN_WIDTH / 2;
  float originY = SCREEN_HEIGHT / 2;
  int sector_arcs_rotation = game->difficulty;
  int player_rotation = game->difficulty;
  time_t t;
  int currentTime = 0;
  srand((unsigned)time(&t));
  game->state = GAME_PLAY;
  game->player_position = 1;
  game->player_triang_posX = (originX + cos(angle) * CENTER_CIRCLE_RADIUS);
  game->player_triang_posY = (originY + sin(angle) * CENTER_CIRCLE_RADIUS);
  game->second_count = 0;
  game->tenth_count = 0;
  game->tenth_of_second_count = 0;
  game->last_time = 0;
  Game_initArcs(game);
  Game_playMusic();

  while (game->state != GAME_OVER) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_RIGHT:
          Player_move_right(game, &angle);
          break;
        case SDLK_LEFT:
          Player_move_left(game, &angle);
          break;
        }
      }
    }

    SDL_SetRenderDrawColor(game->renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(game->renderer);

    Game_drawBackground(game->renderer, &originX, &originY,
                        &sector_arcs_rotation);
    sector_arcs_rotation += game->difficulty;

    filledCircleRGBA(game->renderer, originX, originY,
                     CENTER_CIRCLE_RADIUS - 20, 128, 128, 128, 255);

    Game_drawArcs(game, &originX, &originY, &sector_arcs_rotation);

    Game_resetArcs(game);

    Player_drawTrigon(game->renderer, &game->player_triang_posX,
                      &game->player_triang_posY, &originX, &originY, &angle,
                      &player_rotation);

    Game_checkPlayerState(game);
    currentTime = SDL_GetTicks();
    Game_displayChrono(game, currentTime);

    SDL_RenderPresent(game->renderer);
  }
  Mix_PauseMusic();
}

void Game_delete(struct Game *game) {
  if (game != NULL) {
    free(game);
  }
}

void Player_drawTrigon(SDL_Renderer *renderer, float *player_triang_posX,
                       float *player_triang_posY, const float *originX,
                       const float *originY, float *angle,
                       const int *rotation) {

  *angle += *rotation * PI / 180.0;

  *player_triang_posX = (*originX + cos(*angle) * CENTER_CIRCLE_RADIUS);
  *player_triang_posY = (*originY + sin(*angle) * CENTER_CIRCLE_RADIUS);

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

void Player_move_right(struct Game *game, float *angle) {
  *angle += SECTOR_ANGLE_RADIANT;
  if (game->player_position == PLAYER_POSSIBLE_POSITIONS - 1) {
    game->player_position = 0;
  } else {
    ++game->player_position;
  }
}

void Player_move_left(struct Game *game, float *angle) {
  *angle -= SECTOR_ANGLE_RADIANT;
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

void Game_initArcs(struct Game *game) {

  for (unsigned int i = 0; i < PLAYER_POSSIBLE_POSITIONS; ++i)
    game->arcs[i] = 0;

  for (unsigned int i = 0; i < 3 + game->difficulty; ++i)
    game->arcs[rand() % PLAYER_POSSIBLE_POSITIONS] = 500;
}

void Game_resetArcs(struct Game *game) {
  int arcs_to_reset = 0;
  for (int i = 0; i < PLAYER_POSSIBLE_POSITIONS; ++i) {
    if (game->arcs[i] <= CENTER_CIRCLE_RADIUS - 20 || game->arcs[i] <= 0)
      ++arcs_to_reset;
  }

  if (arcs_to_reset == PLAYER_POSSIBLE_POSITIONS) {
    Game_initArcs(game);
  }
}

void Game_drawArcs(struct Game *game, const float *originX,
                   const float *originY, const int *rotation) {
  for (int i = 0; i < PLAYER_POSSIBLE_POSITIONS; ++i) {
    if (game->arcs[i] != 0) {
      arcRGBA(game->renderer, *originX, *originY, game->arcs[i],
              i * SECTOR_ANGLE_DEGREES + *rotation,
              i * SECTOR_ANGLE_DEGREES + SECTOR_ANGLE_DEGREES + *rotation, 255,
              0, 0, 255);
      arcRGBA(game->renderer, *originX, *originY, game->arcs[i] + 1,
              i * SECTOR_ANGLE_DEGREES + *rotation,
              i * SECTOR_ANGLE_DEGREES + SECTOR_ANGLE_DEGREES + *rotation, 255,
              0, 0, 255);
      arcRGBA(game->renderer, *originX, *originY, game->arcs[i] + 2,
              i * SECTOR_ANGLE_DEGREES + *rotation,
              i * SECTOR_ANGLE_DEGREES + SECTOR_ANGLE_DEGREES + *rotation, 255,
              0, 0, 255);
      arcRGBA(game->renderer, *originX, *originY, game->arcs[i] + 3,
              i * SECTOR_ANGLE_DEGREES + *rotation,
              i * SECTOR_ANGLE_DEGREES + SECTOR_ANGLE_DEGREES + *rotation, 255,
              0, 0, 255);
      game->arcs[i] -= game->difficulty + 3;
    }
  }
}

void Game_checkPlayerState(struct Game *game) {
  for (unsigned int i = 0; i < PLAYER_POSSIBLE_POSITIONS; ++i) {
    if (game->arcs[i] <= CENTER_CIRCLE_RADIUS && game->arcs[i] > 0 &&
        game->player_position == i) {
      game->state = GAME_OVER;
    }
  }
}

void Game_displayChrono(struct Game *game, int currentTime) {
  Spritesheet_render(game->first_digit_sprite, FIRST_DIGIT_X, CHRONO_Y, 255,
                     game->tenth_count);
  Spritesheet_render(game->second_digit_sprite, SECOND_DIGIT_X, CHRONO_Y, 255,
                     game->second_count);
  Spritesheet_render(game->dot_sprite, DOT_X, CHRONO_Y, 255, 10);
  Spritesheet_render(game->third_digit_sprite, THIRD_DIGIT_X, CHRONO_Y, 255,
                     game->tenth_of_second_count);

  if (currentTime > game->last_time + 100) {
    game->last_time = currentTime;
    game->tenth_of_second_count++;
    if (game->tenth_of_second_count > 9) {
      game->tenth_of_second_count = 0;
      game->second_count++;
    }
    if (game->second_count > 9) {
      game->second_count = 0;
      game->tenth_count++;
    }
    if (game->tenth_count > 9) {
      game->tenth_count = 0;
    }
  }
}
void Game_playMusic() {
  Mix_Music *gMusic = NULL;

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n",
           Mix_GetError());
  }

  gMusic = Mix_LoadMUS(MUSIC_FILENAME);
  if (gMusic == NULL) {
    printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
  }
  Mix_PlayMusic(gMusic, -1);
}
