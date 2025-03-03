#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <stdlib.h>

#define WIDTH 500
#define HEIGHT 400
#define CELL_SIZE 20
#define COLOR_ORANGE 0xffa500ff
#define COLOR_RED 0xff0000ff
#define COLOR_GREEN 0x00ff00ff
#define COLOR_BLUE 0x0000ffff
#define COLOR_YELLOW 0xffff00ff
#define COLOR_CYAN 0x00ffffff
#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x00000000
#define COLOR_GRAY 0xefefefef
#define Gravity 9.8
#define RADIUS 4
#define VELOCITY_X 0.0
#define VELOCITY_Y 0.0
#define COEFF_OF_RESTITUTION 0.8

struct Circle {
    double m;
    double x;
    double y;
    double r;
    double velocity_y;
    double velocity_x;
    Uint8 red, green , blue, a;
};

void draw_grid(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 39, 44, 51, 255);
    for (int i = 0; i < WIDTH; i += CELL_SIZE) {
        SDL_RenderDrawLine(renderer, i, 0, i, HEIGHT);
    }
    for (int i = 0; i < HEIGHT; i += CELL_SIZE) {
        SDL_RenderDrawLine(renderer, 0, i, WIDTH, i);
    }
}

void draw_circle(SDL_Renderer *renderer, struct Circle circle, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    for (int y = -circle.r; y <= circle.r; y++) {
        for (int x = -circle.r; x <= circle.r; x++) {
            if (x * x + y * y <= circle.r * circle.r) {
                SDL_RenderDrawPoint(renderer, circle.x + x, circle.y + y);
            }
        }
    }
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Gravity_Ball", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    struct Circle *circles = NULL;
    int circle_count = 0;
    double acceleration = Gravity * 0.001;
    double e = COEFF_OF_RESTITUTION;

    int simulation_running = 1;
    SDL_Event event;

    while (simulation_running) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Background Color
        SDL_RenderClear(renderer);

        // draw_grid(renderer);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                simulation_running = 0;
            }
            if (event.type == SDL_MOUSEMOTION) {
                circle_count++;
                circles = realloc(circles, sizeof(struct Circle) * circle_count);
                printf("Circle %d created at (%d, %d)\n", circle_count, event.button.x, event.button.y);
                printf("Size of circle array: %ld Bytes\n", sizeof(struct Circle) * circle_count);
                circles[circle_count - 1].x = event.button.x;
                circles[circle_count - 1].y = event.button.y;
                circles[circle_count - 1].r = RADIUS;
                circles[circle_count - 1].m = 1.0;
                circles[circle_count - 1].velocity_y = VELOCITY_Y;
                circles[circle_count - 1].velocity_x = VELOCITY_X;
                circles[circle_count - 1].red = rand() % 255;
                circles[circle_count - 1].green = rand() % 255;
                circles[circle_count - 1].blue = rand() % 255;
                circles[circle_count - 1].a = 255;
            }
        }

        for (int i = 0; i < circle_count; i++) {
            circles[i].velocity_y += acceleration;
            circles[i].y += circles[i].velocity_y;
            circles[i].x += circles[i].velocity_x;
            
            if(circles[i].x + circles[i].r > WIDTH){
                circles[i].x = WIDTH - circles[i].r;
                circles[i].velocity_x = -circles[i].velocity_x * e;
            }
            if(circles[i].x - circles[i].r < 0){
                circles[i].x = 0 + circles[i].r;
                circles[i].velocity_x = -circles[i].velocity_x * e;
            }
            if (circles[i].y + circles[i].r > HEIGHT) {
                circles[i].y = HEIGHT - circles[i].r;
                circles[i].velocity_y = -circles[i].velocity_y * e;
            }
            if(circles[i].y - circles[i].r < 0){
                circles[i].y = 0 + circles[i].r;
                circles[i].velocity_y = -circles[i].velocity_y * e;
            }

            // Collision Detection

            for (int j = i + 1; j < circle_count; j++) {
                double dx = circles[i].x - circles[j].x;
                double dy = circles[i].y - circles[j].y;
                double distance = sqrt(dx * dx + dy * dy);
                if (distance < circles[i].r + circles[j].r) {
                    double angle = atan2(dy, dx);
                    double overlap = (circles[i].r + circles[j].r) - distance;

                    circles[i].x += cos(angle) * overlap / 2;
                    circles[i].y += sin(angle) * overlap / 2;
                    circles[j].x -= cos(angle) * overlap / 2;
                    circles[j].y -= sin(angle) * overlap / 2;

                    double nx = dx / distance;
                    double ny = dy / distance;
                    double vix = circles[i].velocity_x;
                    double viy = circles[i].velocity_y;
                    double vjx = circles[j].velocity_x;
                    double vjy = circles[j].velocity_y;

                    double vi = vix * nx + viy * ny;
                    double vj = vjx * nx + vjy * ny;

                    double vi_new = vj + e * (vi - vj);
                    double vj_new = vi + e * (vj - vi);

                    circles[i].velocity_x += (double)rand() / RAND_MAX * 2.0 - 1.0 + (vi_new - vi) * nx;
                    circles[i].velocity_y += (double)rand() / RAND_MAX * 2.0 - 1.0 + (vi_new - vi) * ny;
                    circles[j].velocity_x += (double)rand() / RAND_MAX * 2.0 - 1.0 + (vj_new - vj) * nx;
                    circles[j].velocity_y += (double)rand() / RAND_MAX * 2.0 - 1.0 + (vj_new - vj) * ny;
                }
            
            
        }

            draw_circle(renderer, circles[i], circles[i].red, circles[i].green, circles[i].blue, circles[i].a);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(1); // Approximately 1000 FPS
    }

    free(circles);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}