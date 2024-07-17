#include "particle.h"

/**
 * update_particle - Updates the particle position based
 *                  on it's velocity and acceleration.
 * @p: pointer to the particle
 * @dt: Time step for the update
 */
void update_particle(Particle *p, double dt) {
    /** Update particle based on acceleration */
    p->vx += p->ax * dt;
    p->vy += p->ay * dt;

    /** Update particle based on velocity */
    p->x += p->vx * dt;
    p->y += p->vy * dt;
}

/**
 * render_particle - Renders the particle as a filled circle
 * @renderer: The SDL Renderer.
 * @p: Pointer to the particle.
 */
void render_particle(SDL_Renderer *renderer, Particle *p) {
    SDL_SetRenderDrawColor(renderer, p->color.r, p->color.g, p->color.b, p->color.a);
    // SDL_Rect rect = { (int)(p->x - p->radius), (int)(p->y - p->radius), (int)(2 * p->radius), (int)(2 * p->radius) };
    // SDL_RenderDrawRect(renderer, &rect);

    /* Draw filled circle */
    int centerX = (int)p->x;
    int centerY = (int)p->y;
    int radius = (int)p->radius;

    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }
}
