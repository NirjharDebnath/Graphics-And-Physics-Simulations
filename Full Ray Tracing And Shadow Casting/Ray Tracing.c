#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <time.h>

#define WIDTH 1600
#define HEIGHT 800
#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x00000000
#define COLOR_SOURCE 0xffffffff
#define COLOR_REFLECTION 0xffffffff
#define RAYS_NUMBER 8000
#define MAX_SHADOWS 10
#define MAX_BOUNCES 2

struct Circle {
    double x;
    double y;
    double r;
};

struct Ray {
    double x_start, y_start;
    double dx, dy;
    double intensity;
    int bounce_count;
};

void FillCircle_Outline(SDL_Surface *surface, struct Circle circle, Uint32 color) {
    int x0 = (int)circle.x;
    int y0 = (int)circle.y;
    int radius = (int)circle.r;
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y >= (radius * radius) - 100 && x * x + y * y <= (radius * radius) + 100) {
                int px = x0 + x;
                int py = y0 + y;
                if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT) {
                    Uint32 *pixels = (Uint32 *)surface->pixels;
                    pixels[py * (surface->pitch / 4) + px] = color;
                }
            }
        }
    }
}

void generate_rays(struct Circle circle, struct Ray rays[RAYS_NUMBER]) {
    for (int i = 0; i < RAYS_NUMBER; i++) {
        double angle = ((double)i / RAYS_NUMBER) * 2 * M_PI;
        rays[i] = (struct Ray){
            circle.x, circle.y,
            cos(angle), sin(angle),
            1.0,
            0
        };
    }
}

int RayIntersectsCircle(double x, double y, struct Circle circle) {
    double dx = x - circle.x;
    double dy = y - circle.y;
    double distance_sq = dx * dx + dy * dy;
    return distance_sq <= (circle.r * circle.r);
}

void handle_reflection(struct Ray* ray, double hit_x, double hit_y, struct Circle circle) {
    // Calculate surface normal (vector from circle center to hit point)
    double nx = (hit_x - circle.x) / circle.r;
    double ny = (hit_y - circle.y) / circle.r;
    
    // Normalize incident vector
    double ix = ray->dx;
    double iy = ray->dy;
    double ilen = sqrt(ix * ix + iy * iy);
    if (ilen > 0) {
        ix /= ilen;
        iy /= ilen;
    }
    
    // Calculate reflection vector: R = I - 2*(I·N)*N
    double dot = ix * nx + iy * ny;
    double rx = ix - 2 * dot * nx;
    double ry = iy - 2 * dot * ny;
    
    // Normalize reflection vector
    double rlen = sqrt(rx * rx + ry * ry);
    if (rlen > 0) {
        rx /= rlen;
        ry /= rlen;
    }
    
    // Update ray direction
    ray->dx = rx;
    ray->dy = ry;
    
    // Update ray position (offset to avoid self-intersection)
    ray->x_start = hit_x + rx * 0.01;
    ray->y_start = hit_y + ry * 0.01;
    
    // Reduce intensity and increment bounce count
    ray->intensity *= 0.8;
    ray->bounce_count++;
}

void FillRays(SDL_Surface *surface, struct Ray rays[RAYS_NUMBER], 
              struct Circle objects[], int num_objects, Uint32 baseColor) {
    Uint32 *pixels = (Uint32 *)surface->pixels;
    int pitch = surface->pitch / 4;

    for (int i = 0; i < RAYS_NUMBER; i++) {
        struct Ray current_ray = rays[i];
        
        // Process ray through multiple bounces
        while (current_ray.bounce_count < MAX_BOUNCES && current_ray.intensity > 0.1) {
            double x = current_ray.x_start;
            double y = current_ray.y_start;
            int hit_occurred = 0;
            
            // Trace current ray segment
            for (int step = 0; step < 2000; step++) {
                // Advance ray
                x += current_ray.dx;
                y += current_ray.dy;
                
                // Boundary check
                if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) break;
                
                // Calculate distance-based attenuation
                double dist_sq = (x - rays[i].x_start)*(x - rays[i].x_start)
                               + (y - rays[i].y_start)*(y - rays[i].y_start);
                double intensity = current_ray.intensity * 20000.0 / (dist_sq + 1);
                
                // Apply minimum intensity threshold
                if (intensity < 0.01) break;
                intensity = fmin(intensity, 1.0);
                
                // Determine color based on bounce count
                Uint32 color = baseColor;
                if (current_ray.bounce_count > 0) {
                    color = COLOR_REFLECTION;
                }
                
                // Extract RGB components
                Uint32 r = (color >> 16) & 0xFF;
                Uint32 g = (color >> 8) & 0xFF;
                Uint32 b = color & 0xFF;
                
                // Apply intensity to color
                Uint32 final_color = 
                    ((Uint32)(r * intensity) << 16) |
                    ((Uint32)(g * intensity) << 8) |
                    (Uint32)(b * intensity);
                
                // Blend with existing pixel color
                Uint32 existing = pixels[(int)y * pitch + (int)x];
                Uint32 blended = (existing | final_color);
                pixels[(int)y * pitch + (int)x] = blended;
                
                // Check for collisions with objects
                for (int k = 0; k < num_objects; k++) {
                    if (RayIntersectsCircle(x, y, objects[k])) {
                        handle_reflection(&current_ray, x, y, objects[k]);
                        hit_occurred = 1;
                        break;
                    }
                }
                
                if (hit_occurred) break;
            }
            
            if (!hit_occurred) break;
        }
    }
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("RAY_TRACING", SDL_WINDOWPOS_CENTERED, 
                                          SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Surface *surface = SDL_GetWindowSurface(window);

    struct Circle circle = {200, 200, 20};
    struct Circle shadow_circles[MAX_SHADOWS] = {
        {200, 200, 120},
        {1200, 500, 160},
        {400, 500, 160},
        {800, 300, 100},
        {1200, 200, 100}
    };
    int num_shadows = 5;

    struct Ray rays[RAYS_NUMBER];
    double obstacle_speed_y[MAX_SHADOWS] = {1.0, -0.5, 0.8, -1.2};

    int simulation_running = 1;
    SDL_Event event;
    int circle_moved = 1;
    
    srand(time(NULL));
    generate_rays(circle, rays);

    while (simulation_running) {
        circle_moved = 0;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                simulation_running = 0;
            }
            if (event.type == SDL_MOUSEMOTION && event.motion.state != 0) {
                circle.x = event.motion.x;
                circle.y = event.motion.y;
                circle_moved = 1;
            }
        }

        if (circle_moved) {
            generate_rays(circle, rays);
        }

        SDL_FillRect(surface, NULL, COLOR_BLACK);

        for (int i = 0; i < num_shadows; i++) {
            FillCircle_Outline(surface, shadow_circles[i], COLOR_WHITE);
        }

        FillRays(surface, rays, shadow_circles, num_shadows, COLOR_SOURCE);

        SDL_UpdateWindowSurface(window);
        SDL_Delay(1);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
