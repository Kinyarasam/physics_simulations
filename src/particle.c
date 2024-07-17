#include "particle.h"
#include "main.h"
#include <math.h>

void initialize_particles(Particle particles[], int num_particles) {
    for (int i = 0; i < num_particles; i++) {
        particles[i] = initialize_particle();
	}
}

Particle initialize_particle(void) {
    Particle p;

    double angle = (rand() / (double)RAND_MAX) * 2 * M_PI;
    double radius = (rand() / (double)RAND_MAX) * (BOUNDARY_RADIUS - p.radius);
    
    // Convert polar coordinates to Cartesian coordinates
    p.x = BOUNDARY_CENTER_X + radius * cos(angle);
    p.y = BOUNDARY_CENTER_Y + radius * sin(angle);
    p.vx = ((rand() % 100) / 50.0) - 1; /* Random velocity between -1 and 1 */
    p.vy = ((rand() % 100) / 50.0) - 1;
    p.ax = 0;
    p.ay = 0;
    p.radius = 5;
    p.mass = 1;
    p.color = (SDL_Color){
        (int)(rand() % 255),
        (int)(rand() % 255),
        (int)(rand() % 255),
        (int)(rand() % 255),
        };

    return p;
}

/**
 * update_particle - Updates the particle position based
 *                  on it's velocity and acceleration.
 * @p: pointer to the particle
 * @dt: Time step for the update
 */
void update_particle(Particle *p, double dt) {
    /* Calculate the vector from the boundary center to the particle */
    double dx = p->x - BOUNDARY_CENTER_X;
    double dy = p->y - BOUNDARY_CENTER_Y;
    double distance = sqrt(dx * dx + dy * dy);

    /* Calculate gravitational force */
    double force = 0.0;
    if (distance < BOUNDARY_RADIUS) {
        /* Gravity strongest at the center and weaker at the edges */
        double normalized_distance = distance / BOUNDARY_RADIUS; // Value between 0 and 1
        force = GRAVITY_CONSTANT * (1.0 - normalized_distance); /* Stronger towards the center */
        if (distance > 0) {
            p->ax = force * (-dx / distance); // Pull towards the center
            p->ay = force * (-dy / distance);
        } else {
            p->ax = 0;
            p->ay = 0;
        }
    } else {
        p->ax = 0;
        p->ay = 0;
    }

    /* Update velocities based on acceleration */
    p->vx += p->ax * dt;
    p->vy += p->ay * dt;

    /* Update positions based on velocity */
    p->x += p->vx * dt;
    p->y += p->vy * dt;

    /* Check for boundary collision */
    double boundaryDistance = BOUNDARY_RADIUS - p->radius;
    if (distance > boundaryDistance) {
        double normalX = dx / distance;
        double normalY = dy / distance;
        double dotProduct = p->vx * normalX + p->vy * normalY;

        p->vx -= 2 * dotProduct * normalX;
        p->vy -= 2 * dotProduct * normalY;

        double damping = 0.09;
        p->vx *= damping;
        p->vy *= damping;

        p->x = BOUNDARY_CENTER_X + boundaryDistance * normalX;
        p->y = BOUNDARY_CENTER_Y + boundaryDistance * normalY;
    }
}
//     double dx = p->x - BOUNDARY_CENTER_X;
//     double dy = p->y - BOUNDARY_CENTER_Y;
//     double distance = sqrt(dx * dx + dy * dy);
//     printf("dx: %f   dy: %f   distance: %f\n", dx, dy, distance);

//     if (distance > 0) {
//         double force = GRAVITY_CONSTANT / (distance * distance);
//         printf("force: %f\n", force);
//         p->ax = force * dx / distance;
//         p->ay = force * dy / distance;
//     }

//     p->vx += p->ax * dt;
//     p->vy += p->ay * dt;
//     printf("%f  %f  %f  %f\n", p->ax, p->ay, p->vx, p->vy);

//     p->x += p->vx * dt;
//     p->y += p->vy * dt;

//     printf("BR - p->r: %f\n", BOUNDARY_RADIUS - p->radius);
//     if (distance > BOUNDARY_RADIUS - p->radius) {
//         double normalX = dx / distance;
//         double normalY = dy / distance;
//         double dotProduct = p->vx * normalX + p->vy * normalY;

//         p->vx -= 2 * dotProduct * normalX;
//         p->vy -= 2 * dotProduct * normalY;

//         p->x = BOUNDARY_CENTER_X + (BOUNDARY_RADIUS - p->radius) * normalX;
//         p->y = BOUNDARY_CENTER_Y + (BOUNDARY_RADIUS - p->radius) * normalY;
//     }
// }

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
    draw_circle(renderer, (int)p->x, (int)p->y, (int)p->radius);
}
