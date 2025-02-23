#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>

#define WIDTH 1000
#define HEIGHT 800
#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x00000000
#define COLOR_GRAY 0xefefefef
#define Gravity 9.8
#define COEFF_OF_RESTITUTION 0.8

struct Circle{
    double x;
    double y;
    double r;
};

void draw_circle(SDL_Renderer *renderer, struct Circle circle, Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    for(int y = -circle.r; y <= circle.r; y++){
        for (int x = -circle.r; x <= circle.r; x++){
            if(x*x + y*y <= circle.r*circle.r){
                SDL_RenderDrawPoint(renderer, circle.x + x, circle.y + y);
            }
        }
    }
}

int main(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Gravity_Ball", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    struct Circle circle = {400, 400, 80};
    double velocity = 0;
    double acceleration = Gravity*0.001;
    double e = COEFF_OF_RESTITUTION;

    int simulation_running = 1;
    SDL_Event event;

    while (simulation_running){
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Background Color
        SDL_RenderClear(renderer);
        while(SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                simulation_running = 0;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        velocity += acceleration;
        circle.y += velocity;

        if(circle.y + circle.r > HEIGHT){
            circle.y = HEIGHT - circle.r;
            velocity = -velocity * e;
        }
        draw_circle(renderer, circle, 255, 255, 255, 255);
        SDL_RenderPresent(renderer);
        SDL_Delay(1); // Approximately 60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}