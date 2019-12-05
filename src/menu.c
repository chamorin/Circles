#include "menu.h"
#include "spritesheet.h"
#include "sdl2.h"

#include <stdbool.h>

struct Menu *Menu_initialize(SDL_Renderer *renderer) {
    struct Menu *menu;
    menu = malloc(sizeof(struct Menu));
    menu->renderer = renderer;
    menu->state = MENU_PLAY_FOCUS;
    menu->background = Spritesheet_create(BACKGROUND_FILENAME, 1, 1, 1, renderer);
    menu->title = Spritesheet_create(TITLE_FILENAME, 1, 1, 1, renderer);
    menu->play = Spritesheet_create(PLAY_FILENAME, 1, 1, 1, renderer);
    menu->quit = Spritesheet_create(QUIT_FILENAME, 1, 1, 1, renderer);
    return menu;
}

int Menu_alpha(bool chosen) {
    return chosen ? 255 : 64;
}

void Menu_run(struct Menu *menu) {
    SDL_Event e;
    while (menu->state != MENU_PLAY && menu->state != MENU_QUIT) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                menu->state = MENU_QUIT;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                        menu->state = menu->state == MENU_PLAY_FOCUS ?
                                      MENU_QUIT_FOCUS : MENU_PLAY_FOCUS;
                        break;
                    case SDLK_RIGHT:
                        menu->state = menu->state == MENU_PLAY_FOCUS ?
                                      MENU_QUIT_FOCUS : MENU_PLAY_FOCUS;
                        break;
                    case SDLK_RETURN:
                        if (menu->state == MENU_PLAY_FOCUS) {
                            menu->state = MENU_PLAY;
                        } else if (menu->state == MENU_QUIT_FOCUS) {
                            menu->state = MENU_QUIT;
                        }
                        break;
                }
            }
        }
        SDL_SetRenderDrawColor(menu->renderer, 0x00, 0x00, 0x00, 0x00 );
        SDL_RenderClear(menu->renderer);
        Spritesheet_render(menu->background, BACKGROUND_X, BACKGROUND_Y,
                           255, 0);
        Spritesheet_render(menu->title,      TITLE_X,      TITLE_Y,
                           255, 0);
        Spritesheet_render(menu->play,       PLAY_X,       PLAY_Y,
                           Menu_alpha(menu->state == MENU_PLAY_FOCUS), 0);
        Spritesheet_render(menu->quit,       QUIT_X,       QUIT_Y,
                           Menu_alpha(menu->state == MENU_QUIT_FOCUS), 0);
        SDL_RenderPresent(menu->renderer);
    }
}

void Menu_delete(struct Menu *menu) {
    if (menu != NULL) {
        Spritesheet_delete(menu->background);
        Spritesheet_delete(menu->title);
        Spritesheet_delete(menu->play);
        Spritesheet_delete(menu->quit);
        free(menu);
    }
}
