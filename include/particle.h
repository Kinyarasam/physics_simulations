#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include <SDL2/SDL.h>

typedef struct {
    double x, y;
    double vx, vy;
    double ax, ay;
    double radius;
    double mass;
    SDL_Color color;
} Particle;

Particle initialize_particle(void);
void initialize_particles(Particle particles[], int num_particles);
void update_particle(Particle *p, double dt);
void render_particle(SDL_Renderer *renderer, Particle *p);

#endif /** __PARTICLE_H__ */
