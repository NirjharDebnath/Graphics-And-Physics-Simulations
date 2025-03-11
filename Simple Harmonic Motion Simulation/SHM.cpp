#include <bits/stdc++.h>
#include <SDL2/SDL.h>


#define WHITE {255, 255, 255, 255}
#define BLACK {0, 0, 0, 255}
#define SHM_POINT_COLOR {11, 38, 120, 255}
#define HEIGHT 400
#define WIDTH 1600
#define BODY_SIZE 10
#define SHM_POINT_SIZE 20
#define CELL_SIZE 40
#define NUM_BODIES 1000/CELL_SIZE - 1// Number of SHM bodies

using namespace std;

struct Point{
    int x;
    int y;
};

struct SHM_Point{
    int x;
    int y;
};

struct Circle {
    double x;
    double y;
    double r;
};

// Function to draw a shape centered at (x, y)
void draw_shape(SDL_Renderer *renderer, int x, int y, SDL_Color color) {
    SDL_Rect rect = {x - BODY_SIZE/2, y - BODY_SIZE/2, BODY_SIZE, BODY_SIZE};  
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a); // White color
    SDL_RenderFillRect(renderer, &rect);
}

void draw_point(SDL_Renderer *renderer, int x, int y) {
    SDL_Color color = SHM_POINT_COLOR;
    SDL_Rect rect = {x - SHM_POINT_SIZE/2, y - SHM_POINT_SIZE/2, SHM_POINT_SIZE, SHM_POINT_SIZE}; 
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a); // White color
    SDL_RenderFillRect(renderer, &rect);
}

void draw_grid(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 39, 44, 51, 255);
    for (int i = 0; i < WIDTH; i += CELL_SIZE) {
        SDL_RenderDrawLine(renderer, i, 0, i, HEIGHT);
    }
    for (int i = 0; i < HEIGHT; i += CELL_SIZE) {
        SDL_RenderDrawLine(renderer, 0, i, WIDTH, i);
    }
}

void FillCircle_Outline(SDL_Renderer *renderer, struct Circle circle, SDL_Color color) {
    int x0 = (int)circle.x;
    int y0 = (int)circle.y;
    int radius = (int)circle.r;
    int rSquared = radius * radius;
    int thickness = 400; // Adjust thickness as needed

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    for (int x = -radius; x <= radius; x++) {
        int height = (int)sqrt(rSquared - x * x);
        for (int y = -height; y <= height; y++) {
            int distanceSquared = x * x + y * y;
            if (distanceSquared >= rSquared - thickness && distanceSquared <= rSquared + thickness) {
                SDL_RenderDrawPoint(renderer, x0 + x, y0 + y);
            }
        }
    }
}


int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "SDL Initialization Failed: " << SDL_GetError() << endl;
        return 1;
    }

    // Create SDL window and renderer
    SDL_Window *window = SDL_CreateWindow("Simple Harmonic Motion", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);   
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    // SHM Parameters
    int EQUILIBRIUM_X = WIDTH / 2;      // Equilibrium point (horizontal)
    int EQUILIBRIUM_Y = HEIGHT / 2;      // Start vertical position
    double amplitude = 160;       // Amplitude of motion
    double omega = -0.05;          // Angular frequency (speed of oscillation)
    struct Point points[NUM_BODIES];
    struct SHM_Point shm_point;
    struct Circle SHM_circle = {200, 200, 40};
    // Array to store phase offsets for each body
    double phase_offsets[NUM_BODIES];

    SDL_Color white_color = WHITE;

    // Initialize phase offsets to create a wave pattern
    for (int i = 0; i < NUM_BODIES; i++) {
        phase_offsets[i] = i * 0.5; // Spread out phases
    }

    Uint32 frameStart, frameEnd, frameTime;
    double fps;

    // Time counter for SHM
    double t = 0;

    // Main loop
    bool simulation_running = true;
    SDL_Event event;

    while (simulation_running) {
        // Background color (black)

        frameStart = SDL_GetTicks();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                simulation_running = false; // Exit loop on window close
            }
        }
        draw_grid(renderer);
        SDL_SetRenderDrawColor(renderer, white_color.r, white_color.g, white_color.b, white_color.a);
        SDL_RenderDrawLine(renderer, 0, HEIGHT/2, WIDTH, HEIGHT/2);
        SDL_RenderDrawLine(renderer, WIDTH/2, 0, WIDTH/2, HEIGHT);
        // Draw multiple SHM bodies
        for (int i = 0; i < NUM_BODIES; i++) {
            points[i].y = EQUILIBRIUM_Y + static_cast<int>(amplitude * sin(omega * t + phase_offsets[i]));
            points[i].x = 16*CELL_SIZE + i * CELL_SIZE; // Vertical spacing between bodies

            SDL_SetRenderDrawColor(renderer, white_color.r, white_color.g, white_color.b, white_color.a);
            SDL_RenderDrawLine(renderer, points[i].x, points[i].y, points[i].x, HEIGHT/2);
            draw_shape(renderer, points[i].x, points[i].y, white_color);

            SHM_circle.x = 8*CELL_SIZE;
            SHM_circle.y = EQUILIBRIUM_Y;
            SHM_circle.r = amplitude;
            FillCircle_Outline(renderer, SHM_circle, white_color);

            shm_point.x = SHM_circle.x + SHM_circle.r * cos(omega * t + phase_offsets[0]);
            shm_point.y = SHM_circle.y + SHM_circle.r * sin(omega * t + phase_offsets[0]);
            draw_point(renderer, shm_point.x, shm_point.y);

            SDL_SetRenderDrawColor(renderer, white_color.r-100, white_color.g-100, white_color.b-100, white_color.a);
            SDL_RenderDrawLine(renderer, shm_point.x, shm_point.y, points[0].x, points[0].y);

            SDL_SetRenderDrawColor(renderer, white_color.r, white_color.g, white_color.b, white_color.a);
            SDL_RenderDrawLine(renderer, SHM_circle.x, SHM_circle.y, shm_point.x, shm_point.y);

            if (i<NUM_BODIES-1){
                SDL_SetRenderDrawColor(renderer, white_color.r, white_color.g, white_color.b, white_color.a);
                SDL_RenderDrawLine(renderer, points[i].x, points[i].y, points[i+1].x, points[i+1].y);
            }
        }
        
        // Increase time to progress SHM
        t += 1;
        SDL_RenderPresent(renderer);
        
        // Render the frame
        frameEnd = SDL_GetTicks(); 
        frameTime = frameEnd - frameStart; 
        fps = 1000.0 / frameTime;
        printf("FPS: %.2f\n", fps);

        

        // Delay to control frame rate
        SDL_Delay(1);
    }

    // Clean up SDL resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
