# Gravity Ball Simulation 🎮🌍

## Overview 📜

This project simulates the behavior of multiple balls under the influence of gravity, resembling the nature of an ideal gas. The simulation is implemented using the **SDL2** library in **C**. Each ball is represented as a circle with properties such as mass, position, velocity, and color. The balls interact with each other and the boundaries of the window, demonstrating elastic collisions and gravitational acceleration.

## Features ✨

- **Gravity Simulation**: Balls accelerate downward due to gravity.
- **Elastic Collisions**: Balls collide with each other and the walls, conserving momentum and energy.
- **Randomized Colors**: Each ball is assigned a random color upon creation.
- **Mouse Interaction**: Create new balls by moving the mouse within the window.
- **Real-time Rendering**: The simulation runs in real-time with a high frame rate.

## Dependencies 📦

- **SDL2**: Simple DirectMedia Layer is used for rendering and handling input.
- **math.h**: Standard C library for mathematical functions.
- **stdlib.h**: Standard C library for memory allocation and random number generation.

## Installation 🛠️

1. **Install SDL2**:
   - On Ubuntu: `sudo apt-get install libsdl2-dev`
   - On macOS: `brew install sdl2`
   - On Windows: Download the development libraries from the [SDL2 website](https://www.libsdl.org/download-2.0.php).

2. **Compile the Code**:
   ```bash
   gcc -o gravity_ball gravity_ball.c -lSDL2 -lm
   ```

3. **Run the Simulation**:
   ```bash
   ./gravity_ball
   ```

## Code Structure 🧩

### Constants and Definitions

```c
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
```

### Data Structures

```c
struct Circle {
    double m; // Mass
    double x; // X position
    double y; // Y position
    double r; // Radius
    double velocity_y; // Y velocity
    double velocity_x; // X velocity
    Uint8 red, green, blue, a; // Color components
};
```

### Functions

- **`draw_grid(SDL_Renderer *renderer)`**: Draws a grid on the screen (currently commented out).
- **`draw_circle(SDL_Renderer *renderer, struct Circle circle, Uint8 r, Uint8 g, Uint8 b, Uint8 a)`**: Draws a circle on the screen.

### Main Function

The main function initializes the SDL window and renderer, handles user input, updates the positions and velocities of the balls, and renders them on the screen.

```c
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
```

## Physics Behind the Simulation 🧪

### Gravity

The balls are subject to a constant gravitational acceleration \( g = 9.8 \, \text{m/s}^2 \). This is implemented by updating the vertical velocity of each ball in every frame:

\[
v_y = v_y + g \cdot \Delta t
\]

where \( \Delta t \) is the time step.

### Collision Detection and Response

Collisions between balls are detected by checking if the distance between their centers is less than the sum of their radii:

\[
\text{distance} = \sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2} < r_1 + r_2
\]

When a collision is detected, the balls are moved apart to resolve the overlap, and their velocities are updated based on the conservation of momentum and the coefficient of restitution \( e \).

### Boundary Collisions

When a ball collides with the boundaries of the window, its velocity is reversed and scaled by the coefficient of restitution:

\[
v_x = -e \cdot v_x \quad \text{or} \quad v_y = -e \cdot v_y
\]

## Future Enhancements 🚀

- **User Interface**: Add buttons and sliders to control simulation parameters.
- **Advanced Physics**: Implement air resistance and friction.
- **Optimization**: Improve collision detection efficiency using spatial partitioning techniques.

## Conclusion 🎉

This simulation provides a simple yet effective demonstration of physics principles in action. It's a great starting point for those interested in game development, physics simulations, or just having fun with code! 🎈

---

**Happy Coding!** 🚀👨‍💻👩‍💻
