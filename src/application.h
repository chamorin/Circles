#ifndef APPLICATION_H
#define APPLICATION_H

#include "sdl2.h"
#include "constants.h"
#include "menu.h"
#include "player.h"

// --------------- //
// Data structures //
// --------------- //

enum ApplicationState {
    APPLICATION_STATE_MENU, // We show the menu
    APPLICATION_STATE_PLAY, // We are playing
    APPLICATION_STATE_QUIT  // We are quitting
};

struct Application {
    enum ApplicationState state;                // The current state
    struct Menu *menu;                          // The home menu
    struct Player *player;                      // The playable component
    int positions[PLAYER_POSSIBLE_POSITIONS];   // Player position on scene
    SDL_Window* window;                         // The window
    SDL_Renderer* renderer;                     // The renderer
};

// --------- //
// Functions //
// --------- //

/**
 * Creates a new application.
 *
 * @return  A pointer to a new application, NULL if there was an error
 */
struct Application *Application_initialize();

/**
 * Start running the application.
 *
 * @param application  The application to run
 */
void Application_run(struct Application *application);

/**
 * Closes the given application.
 *
 * @param application  The application to be closed
 */
void Application_shutDown(struct Application *application);

#endif
