#ifndef MENU_H
#define MENU_H

#include "sdl2.h"
#include "constants.h"

// --------------- //
// Data structures //
// --------------- //

enum MenuState {
    MENU_PLAY_FOCUS,       // Play choice has focus
    MENU_QUIT_FOCUS,       // Quit choice has focus
    MENU_PLAY,             // Play has been chosen
    MENU_QUIT              // Play has been chosen
};

struct Menu {
    enum MenuState state;           // The choice of the user
    struct Spritesheet *background; // The menu background
    struct Spritesheet *title;      // The title sprite
    struct Spritesheet *play;       // The play sprite
    struct Spritesheet *quit;       // The quit sprite
    SDL_Renderer *renderer;         // The renderer
};

// --------- //
// Functions //
// --------- //

/**
 * Creates a new menu.
 *
 * @param renderer  The renderer
 * @return          A pointer to the menu, NULL if there was an error
 */
struct Menu *Menu_initialize(SDL_Renderer *renderer);

/**
 * Start running the menu.
 *
 * @param menu  The menu to show
 */
void Menu_run(struct Menu *menu);

/**
 * Delete the menu.
 *
 * @param menu  The menu to delete
 */
void Menu_delete(struct Menu *menu);

#endif
