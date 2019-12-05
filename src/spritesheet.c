#include "spritesheet.h"

struct Spritesheet *Spritesheet_create(const char *filename,
                                       int numRows,
                                       int numColumns,
                                       int numSprites,
                                       SDL_Renderer* renderer) {
	struct Spritesheet *spritesheet;
    spritesheet = (struct Spritesheet*)malloc(sizeof(struct Spritesheet));
    spritesheet->numRows = numRows;
    spritesheet->numColumns = numColumns;
    spritesheet->numSprites = numSprites;
    spritesheet->scale = 1.0;
	spritesheet->texture = NULL;
	spritesheet->renderer = renderer;
	SDL_Surface *loadedSurface = IMG_Load(filename);
	if (loadedSurface == NULL) {
		printf("Unable to load image %s: %s\n",
               filename, IMG_GetError());
	} else {
        spritesheet->texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (spritesheet->texture == NULL) {
			printf("Unable to create texture from %s: %s\n",
                   filename, SDL_GetError());
        }
        spritesheet->spriteWidth = loadedSurface->w / numColumns;
        spritesheet->spriteHeight = loadedSurface->h / numRows;
        SDL_FreeSurface(loadedSurface);
	}
    return spritesheet;
}

void Spritesheet_delete(struct Spritesheet *spritesheet) {
    SDL_DestroyTexture(spritesheet->texture);
    free(spritesheet);
}

void Spritesheet_render(struct Spritesheet *spritesheet,
                        int x, int y, int alpha, int sprite) {
    int srcx = spritesheet->spriteWidth * (sprite % spritesheet->numColumns);
    int srcy = spritesheet->spriteHeight * (sprite / spritesheet->numColumns);
    SDL_Rect srcrect = {srcx, srcy, spritesheet->spriteWidth, spritesheet->spriteHeight};
    SDL_Rect dstrect = {x, y, (int)(spritesheet->scale * spritesheet->spriteWidth),
                              (int)(spritesheet->scale * spritesheet->spriteHeight)};
    SDL_SetTextureAlphaMod(spritesheet->texture, alpha);
	SDL_RenderCopy(spritesheet->renderer, spritesheet->texture, &srcrect, &dstrect);
}
