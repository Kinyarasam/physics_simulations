#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "main.h"
#include "particle.h"


#define NUM_PARTICLES 100


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
	for (int i = 0; i < NUM_PARTICLES; i++) {
		particles[i].x = rand() % SCREEN_WIDTH;
		particles[i].y = rand() % SCREEN_HEIGHT;
		particles[i].vx = ((rand() % 100) / 50.0) - 1; /* Random velocity between -1 and 1 */
		particles[i].vy = ((rand() % 100) / 50.0) - 1;
		particles[i].ax = 0;
		particles[i].ay = 0;
		particles[i].radius = 5;
		particles[i].mass = 1;
		particles[i].color = (SDL_Color){
			(int)(rand() % 255),
			(int)(rand() % 255),
			(int)(rand() % 255),
			(int)(rand() % 255),
			};
	}

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

				default:
					break;
			}
		}

		/* Update Particles */
		for (int i = 0; i < NUM_PARTICLES; i++) {
			update_particle(&particles[i], 0.5); /* Assuming 60fps, dt = 1/60 */
		}

		/* Render */
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

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
