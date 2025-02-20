// compile gcc Ray_Tracing.c -o Ray_Tracing -lSDL2
// run ./Ray_Tracing

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>

#define WIDTH 1600
#define HEIGHT 800
#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x00000000
#define COLOR_GRAY 0xefefefef
#define COLOR_SOURCE 0xFFFAAB3C
#define RAYS_NUMBER 1000

struct Circle{
    double x;
    double y;
    double r;
};

struct Ray{
    double x_start, y_start;
    double angle;
};

void FillCircle(SDL_Surface *surface, struct Circle circle, Uint32 color){
    int x0 = (int)circle.x;
    int y0 = (int)circle.y;
    int radius = (int)circle.r;
    for (int y = -radius; y <= radius; y++){
        for (int x = -radius; x <= radius; x++){
            if (x * x + y * y <= radius * radius){
                int px = x0 + x;
                int py = y0 + y;
                if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT){
                    Uint32 *pixels = (Uint32 *)surface->pixels;
                    pixels[py * (surface->pitch / 4) + px] = color;
                }
            }
        }
    }
}

void generate_rays(struct Circle circle, struct Ray rays [RAYS_NUMBER]){
    for (int i = 0; i < RAYS_NUMBER; i++){
        double angle = ((double)i / RAYS_NUMBER) * 2 * M_PI;
        rays[i] = (struct Ray){circle.x, circle.y, angle};
    }
}

void FillRays(SDL_Surface *surface, struct Ray rays[RAYS_NUMBER], struct Circle object, Uint32 color){
    Uint32 *pixels = (Uint32 *)surface->pixels;
    int pitch = surface->pitch / 4;
    for (int i = 0; i < RAYS_NUMBER; i++){
        struct Ray ray = rays[i];
        double x = ray.x_start, y = ray.y_start;
        double dx = cos(ray.angle), dy = sin(ray.angle);
        double x_c = object.x, y_c = object.y;
        double radius_squared = object.r * object.r;
        
        for (int j = 0; j < WIDTH; j++){
            int ix = (int)x, iy = (int)y;
            if (ix < 0 || ix >= WIDTH || iy < 0 || iy >= HEIGHT) break;
            pixels[iy * pitch + ix] = color;
            if (((x - x_c) * (x - x_c) + (y - y_c) * (y - y_c)) <= radius_squared) break;
            x += dx; y += dy;
        }
    }
}

int main(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("RAY_TRACING", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Surface *surface = SDL_GetWindowSurface(window);

    struct Circle circle = {200, 200, 40};
    struct Circle shadow_circle = {1200, 500, 160};
    SDL_Rect erase_rect = {0, 0, WIDTH, HEIGHT};
    struct Ray rays[RAYS_NUMBER];
    double obstacle_speed_y = 0.2;

    int simulation_running = 1;
    SDL_Event event;
    while (simulation_running){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                simulation_running = 0;
            }
            if (event.type == SDL_MOUSEMOTION && event.motion.state != 0){
                circle.x = event.motion.x;
                circle.y = event.motion.y;
                generate_rays(circle, rays);
            }
        }

        SDL_FillRect(surface, &erase_rect, COLOR_BLACK);
        FillCircle(surface, shadow_circle, COLOR_WHITE);
        FillRays(surface, rays, shadow_circle, COLOR_SOURCE);
        FillCircle(surface, circle, COLOR_WHITE);

        shadow_circle.y += obstacle_speed_y;
        if (shadow_circle.y - shadow_circle.r < 0 || shadow_circle.y + shadow_circle.r > HEIGHT){
            obstacle_speed_y = -obstacle_speed_y;
        }

        SDL_UpdateWindowSurface(window);
        SDL_Delay(1);
    }
    
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
