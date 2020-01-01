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
 * Draw player triangle
 * 
 * @param renderer              The renderer
 * @param player_triang_posX    The player position on the X axis
 * @param player_triang_posY    The player position on the Y axis
 * @param originX               The X position of the origin of the center circle
 * @param originY               The Y position of the origin of the center circle
 * @param angle                 The angle to draw the triangle on
 * @param rotation              The rotation angle to draw the triangle on
 */
void Player_drawTrigon(SDL_Renderer *renderer, float *player_triang_posX,
                       float *player_triang_posY, const float *originX,
                       const float *originY, float *angle, const int *rotation);

/**
 * Change player position in right direction
 * 
 * @param game  The instance of the game
 * @param angle The angle to draw the triangle on
 */
void Player_move_right(struct Game *game, float *angle);

/**
 * Change player position in left direction
 * 
 * @param game  The instance of the game
 * @param angle The angle to draw the triangle on
 */
void Player_move_left(struct Game *game, float *angle);

/**
 * Draw game background
 * 
 * @param renderer  The renderer
 * @param originX   The X position of the origin of the center circle
 * @param originY   The Y position of the origin of the center circle
 * @param rotation  The rotation to draw the sector on
 */
void Game_drawBackground(SDL_Renderer *renderer, const float *originX,
                         const float *originY, const int *rotation);

/**
 * Initialise game arcs
 * 
 * @param game  The instance of the game
 */
void Game_initArcs(struct Game *game);

/**
 * Reset game arcs
 * 
 * @param game  The instance of the game
 */
void Game_resetArcs(struct Game *game);

/**
 * Draw game arcs on screen
 * 
 * @param game      The instance of the game
 * @param originX   The X position of the origin of the center circle
 * @param originY   The Y position of the origin of the center circle
 * @param rotation  The rotation to draw the arc on
 */
void Game_drawArcs(struct Game *game, const float *originX,
                   const float *originY, const int *rotation);

/**
 * Check player status
 * 
 * @param game  The instance of the game
 */
void Game_checkPlayerState(struct Game *game);

/**
 * Play music in game
 */
void Game_playMusic();

#endif
