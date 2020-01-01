#ifndef GAME_H
#define GAME_H

#include "constants.h"
#include "sdl2.h"

// --------------- //
// Data structures //
// --------------- //

enum GameState {
  GAME_PLAY, // Game state when playing
  GAME_OVER  // Game state when losing or not playing
};

enum Difficulty { EASY, MEDIUM, HARD };

struct Game {
  enum GameState state;                 // The game state
  enum Difficulty difficulty;           // The game level of difficulty
  float player_triang_posX;             // The player triangle tip X position
  float player_triang_posY;             // The player triangle tip Y position
  unsigned int player_position;         // The player current position in positions table
  int arcs[PLAYER_POSSIBLE_POSITIONS];  // The arcs in the game
  SDL_Renderer *renderer;               // The renderer
};

// --------- //
// Functions //
// --------- //

/**
 * Creates a new game.
 *
 * @param renderer  The renderer
 * @return          A pointer to the game, NULL if there was an error
 */
struct Game *Game_initialize(SDL_Renderer *renderer);

/**
 * Start running the game instance.
 *
 * @param game  The game to show
 */
void Game_run(struct Game *game);

/**
 * Delete the game.
 *
 * @param game  The game to delete
 */
void Game_delete(struct Game *game);

/**
 *
 */
void Player_drawTrigon(SDL_Renderer *renderer, float *player_triang_posX,
                       float *player_triang_posY, const float *originX,
                       const float *originY, float *angle, const int *rotation);

/**
 *
 */
void Player_move_right(struct Game *game, float *angle);

/**
 *
 */
void Player_move_left(struct Game *game, float *angle);

/**
 *
 */
void Game_drawBackground(SDL_Renderer *renderer, const float *originX,
                         const float *originY, const int *rotation);

/**
 *
 */
void Game_initArcs(struct Game *game);

/**
 *
 */
void Game_resetArcs(struct Game *game);

/**
 *
 */
void Game_drawArcs(struct Game *game, const float *originX,
                   const float *originY, const int *rotation);

/**
 *
 */
void Game_checkPlayerState(struct Game *game);

#endif
