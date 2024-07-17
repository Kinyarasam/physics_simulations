#ifndef __MAIN_H__
#define __MAIN_H__

#include <SDL2/SDL.h>

#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH 1000
#define BOUNDARY_RADIUS (SCREEN_HEIGHT / 2 - 100)
#define BOUNDARY_CENTER_X (SCREEN_WIDTH / 2)
#define BOUNDARY_CENTER_Y (SCREEN_HEIGHT / 2)

#define GRAVITY_CONSTANT 100.0

void draw_circle(SDL_Renderer *renderer, int centerX, int centerY, int radius);

#endif /** __MAIN_H__ */
