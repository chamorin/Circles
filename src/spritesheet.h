#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "sdl2.h"

struct Spritesheet {
    int numRows;            // The number of rows in the sprite sheet
    int numColumns;         // The number of columns in the sprite sheet
    int numSprites;         // The total number of sprites
    int spriteWidth;        // The width of an individual sprite
    int spriteHeight;       // The height of an individual sprite
    float scale;            // The scale of the rendered sprite
    SDL_Texture *texture;   // The texture (image) of the sprite sheet
    SDL_Renderer *renderer; // The renderer
};

/**
 * Creates a sprite sheet.
 *
 * @param filename    The filename of the sprite sheet image
 * @param numRows     The number of rows in the sprite sheet
 * @param numColumns  The number of columns in the sprite sheet
 * @param numSprites  The total number of sprites
 * @param renderer    The renderer used for loading the sprite sheet
 * @return            The sprite sheet
 */
struct Spritesheet *Spritesheet_create(const char *filename,
                                       int numRows, int numColumns,
                                       int numSprites, SDL_Renderer* renderer);

/**
 * Delete the sprite sheet.
 *
 * @param spritesheet  The spritesheet to delete
 */
void Spritesheet_delete(struct Spritesheet *spritesheet);

/**
 * Renders the current sprite.
 *
 * @param spritesheet  The spritesheet to render
 * @param x            The top-left corner x-coordinate for the render
 * @param y            The top-left corner y-coordinate for the render
 * @param alpha        The transparence when rendering
 * @param sprite       The sprite to render
 */
void Spritesheet_render(struct Spritesheet *spritesheet,
                        int x, int y, int alpha, int frame);

#endif
