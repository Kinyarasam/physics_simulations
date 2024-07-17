#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "main.h"
#include "particle.h"

#define NUM_PARTICLES 100


/**
 * draw_circle - Draws a circle outline.
 * @renderer: The SDL Renderer
 * @centerX: The x-coordinates of the circle's center.
 * @centerY: The y-coordinates of the circle's center.
 * @radius: The radius of the circle
 */
void draw_circle(SDL_Renderer *renderer, int centerX, int centerY, int radius) {
	int offsetX, offsetY, d;
	int status;

	offsetX = 0;
	offsetY = radius;
	d = radius -1;
	status = 0;

	while (offsetY >= offsetX) {
		status += SDL_RenderDrawPoint(renderer, centerX + offsetX, centerY + offsetY);
        status += SDL_RenderDrawPoint(renderer, centerX + offsetY, centerY + offsetX);
        status += SDL_RenderDrawPoint(renderer, centerX - offsetX, centerY + offsetY);
        status += SDL_RenderDrawPoint(renderer, centerX - offsetY, centerY + offsetX);
        status += SDL_RenderDrawPoint(renderer, centerX + offsetX, centerY - offsetY);
        status += SDL_RenderDrawPoint(renderer, centerX + offsetY, centerY - offsetX);
        status += SDL_RenderDrawPoint(renderer, centerX - offsetX, centerY - offsetY);
        status += SDL_RenderDrawPoint(renderer, centerX - offsetY, centerY - offsetX);

		if (status < 0) {
			status -= 1;
			break;
		}

		if (d >= 2*offsetX) {
            d -= 2*offsetX + 1;
            offsetX +=1;
        } else if (d < 2 * (radius - offsetY)) {
            d += 2*offsetY -1;
            offsetY -= 1;
        } else {
            d += 2*(offsetY - offsetX - 1);
            offsetY -= 1;
            offsetX += 1;
        }
	}
}


/**
 * main - Entry File.
 *
 * Returns: always 0 on success.
 * 	    otherwise 1.
 */
int main(void) {
	/** Initialize SDL */
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Failed to Initialize SDL: %s\n", SDL_GetError());
		return (1);
	}

	/** Create Window */
	SDL_Window *window = SDL_CreateWindow("Simulations", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (!window) {
		fprintf(stderr, "Failed to Create window: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}

	/** Create Renderer */
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return (1);
	}

	/** Create particles */
	Particle particles[NUM_PARTICLES];
	initialize_particles(particles, NUM_PARTICLES);

	/** Main loop */
	bool running = true;
	SDL_Event event;
	while (running) {
		while (SDL_PollEvent(&event)) {
			switch (event.type)
			{
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_r) {
						initialize_particles(particles, NUM_PARTICLES);
					}

				default:
					break;
			}
		}

		/* Update Particles */
		for (int i = 0; i < NUM_PARTICLES; i++) {
			update_particle(&particles[i], 0.16); /* Assuming 60fps, dt = 1/60 */
		}


		/* Render */
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		/* Draw the circular boundary */
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		draw_circle(renderer, BOUNDARY_CENTER_X, BOUNDARY_CENTER_Y, BOUNDARY_RADIUS);

		for (int i = 0; i < NUM_PARTICLES; i++) {
			render_particle(renderer, &particles[i]);
		}

		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return (0);
}
