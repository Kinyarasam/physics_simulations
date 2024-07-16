#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "main.h"


/**
 * main - Entry File.
 *
 * Returns: always 0 on success.
 * 	    otherwise 1.
 */
int main(void) {
	if (SDL_Init(SDL_INIT_VIDEO) > 0) {
		fprintf(stderr, "Failed to Initialize SDL: %s\n", SDL_GetError());
		return (1);
	}

	SDL_Window *window = SDL_CreateWindow(
		"Simulations",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT, 0
	);
	if (!window) {
		fprintf(stderr, "Failed to Create window: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window,
												-1,
												SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return (1);
	}

	bool ACTIVE = true;
	SDL_Event event;

	while (ACTIVE) {
		while (SDL_PollEvent(&event)) {
			switch (event.type)
			{
				case SDL_QUIT:
					ACTIVE = false;
					break;
				
				default:
					break;
			}
		}

		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return (0);
}
