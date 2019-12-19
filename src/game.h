#ifndef GAME_H
#define GAME_H

#include "sdl2.h"
#include "constants.h"

// --------------- //
// Data structures //
// --------------- //

enum GameState {
    GAME_PLAY,  // Game state when playing
    GAME_OVER   // Game state when losing or not playing
};

struct Game {
    enum GameState state;               // The game state
    struct Spritesheet *background;     // The game background sprite
    struct Spritesheet *player_sprite;  // The player sprite
    float player_sprite_posX;           // The player sprite X position
    float player_sprite_posY;           // The player sprite Y position
    unsigned int player_position;       // The player current position in positions table
    SDL_Renderer *renderer;             // The renderer
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

#endif
