#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>

#define WIDTH 1600
#define HEIGHT 800
#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x00000000
#define COLOR_SOURCE 0xFFdefafc
#define RAYS_NUMBER 2000 // It is computationally hard
#define MAX_SHADOWS 10

struct Circle {
    double x;
    double y;
    double r;
};

struct Ray {
    double x_start, y_start;
    double angle;
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
        rays[i] = (struct Ray){circle.x, circle.y, angle};
    }
}

int RayIntersectsCircle(double x, double y, struct Circle circle) {
    double dx = x - circle.x;
    double dy = y - circle.y;
    return (dx * dx + dy * dy) <= (circle.r * circle.r);
}

void FillRays(SDL_Surface *surface, struct Ray rays[RAYS_NUMBER], struct Circle objects[], int num_objects, Uint32 baseColor) {
    Uint32 *pixels = (Uint32 *)surface->pixels;
    int pitch = surface->pitch / 4;

    for (int i = 0; i < RAYS_NUMBER; i++) {
        struct Ray ray = rays[i];
        double x = ray.x_start, y = ray.y_start;
        double dx = cos(ray.angle), dy = sin(ray.angle);

        for (int j = 0; j < WIDTH; j++) {
            int ix = (int)x, iy = (int)y;
            if (ix < 0 || ix >= WIDTH || iy < 0 || iy >= HEIGHT) break;

            double distance_squared = (x - ray.x_start) * (x - ray.x_start) + (y - ray.y_start) * (y - ray.y_start);
            double intensity = 40000.0 / (distance_squared + 1.0);
            if (intensity > 1.0) intensity = 1.0;
            if (intensity < 0.05) intensity = 0.0;

            Uint32 r = (baseColor >> 16) & 0xFF;
            Uint32 g = (baseColor >> 8) & 0xFF;
            Uint32 b = baseColor & 0xFF;

            r = (Uint32)(r * intensity);
            g = (Uint32)(g * intensity);
            b = (Uint32)(b * intensity);

            Uint32 newColor = (r << 16) | (g << 8) | b;
            pixels[iy * pitch + ix] = newColor;

            for (int k = 0; k < num_objects; k++) {
                if (RayIntersectsCircle(x, y, objects[k])) {
                    j = WIDTH; // Stop the ray if it intersects any circle
                    break;
                }
            }

            x += dx;
            y += dy;
        }
    }
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("RAY_TRACING", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
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

    while (simulation_running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                simulation_running = 0;
            }
            if (event.type == SDL_MOUSEMOTION && event.motion.state != 0) {
                circle.x = event.motion.x;
                circle.y = event.motion.y;
                generate_rays(circle, rays);
            }
        }

        SDL_FillRect(surface, NULL, COLOR_BLACK);

        for (int i = 0; i < num_shadows; i++) {
            FillCircle_Outline(surface, shadow_circles[i], COLOR_WHITE);
            // shadow_circles[i].y += obstacle_speed_y[i];

            // if (shadow_circles[i].y - shadow_circles[i].r < 0 || shadow_circles[i].y + shadow_circles[i].r > HEIGHT) {
            //     obstacle_speed_y[i] = -obstacle_speed_y[i];
            // }
        }

        FillRays(surface, rays, shadow_circles, num_shadows, COLOR_SOURCE);

        SDL_UpdateWindowSurface(window);
        SDL_Delay(1);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
