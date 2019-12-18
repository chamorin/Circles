#ifndef PLAYER_H
#define PLAYER_H

#include "sdl2.h"
#include "constants.h"

// --------------- //
// Data structures //
// --------------- //

enum PlayerState {
    PLAYER_ALIVE,   // Player state when playing
    PLAYER_DEAD     // Player state when losing or not playing
};

struct Player {
    enum PlayerState state;             // The player state
    struct Spritesheet *player_sprite;  // The player sprite
    SDL_Renderer *renderer;             // The renderer
};

// --------- //
// Functions //
// --------- //

/**
 * Creates a new player.
 *
 * @param renderer  The renderer
 * @return          A pointer to the player, NULL if there was an error
 */
struct Player *Player_initialize(SDL_Renderer *renderer);

/**
 * Start running the player instance.
 *
 * @param player  The player to show
 */
void Player_run(struct Player *player);

/**
 * Delete the player.
 *
 * @param player  The player to delete
 */
void Player_delete(struct Player *player);

#endif
