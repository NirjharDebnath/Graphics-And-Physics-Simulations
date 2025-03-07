# 🌟 Ray Tracing and Shadow Casting Simulation 

This project implements a **ray tracing-based shawdow casting simulation** using **SDL2** in **C**. It simulates light rays originating from a moving source that interact with multiple circular obstacles (shadow-casting objects). The simulation features:

✅ **Real-time light propagation**  
✅ **Dynamic circle obstacles**  
✅ **Adjustable ray count for performance vs. accuracy**  
✅ **Smooth motion and collision detection**

## 🧪 Physics Behind the Simulation

### 1. Ray Propagation
- Each ray originates from the light source and propagates in a straight line.
- The rays are defined by their starting position and angle:

```c
struct Ray {
    double x_start, y_start;
    double angle;
};
```
- We calculate the ray's new position using **trigonometry**:

x = x + ∆x , y = y + ∆y

Where:
- ∆x = cos(theta)
- ∆y = sin(theta)

### 2. Circle Intersection (Shadow Detection)
For each ray, we check if it intersects any circle using the **point-circle collision** formula:

(x - x_c)² + (y - y_c)² <= r²

Where:
- \( (x_c, y_c) \) is the circle center
- \( r \) is the circle radius

If the ray intersects any circle, it stops propagating, simulating a **shadow**.

### 3. Light Intensity Calculation
The intensity of light decreases with distance, following the **inverse-square law**:

- I = I_0/(d^2 + 1)

Where:
- \( I_0 \) is the initial intensity
- \( d \) is the distance from the light source

To avoid division by zero, a small offset (+1) is added.

The color of each ray is scaled according to its intensity:

```c
Uint32 r = (baseColor >> 16) & 0xFF;
Uint32 g = (baseColor >> 8) & 0xFF;
Uint32 b = baseColor & 0xFF;

r = (Uint32)(r * intensity);
g = (Uint32)(g * intensity);
b = (Uint32)(b * intensity);
```

### 4. Dynamic Object Motion
Obstacles can move vertically, reflecting when hitting screen edges:

```c
shadow_circles[i].y += obstacle_speed_y[i];
if (shadow_circles[i].y - shadow_circles[i].r < 0 || shadow_circles[i].y + shadow_circles[i].r > HEIGHT) {
    obstacle_speed_y[i] = -obstacle_speed_y[i];
}
```

## 📦 Dependencies
- SDL2 (Simple DirectMedia Layer) library

Ensure SDL2 is installed on your system:

### Ubuntu (Linux)
```bash
sudo apt-get install libsdl2-dev
```

### macOS
```bash
brew install sdl2
```

## 🚀 How to Compile and Run
1. Ensure SDL2 is installed.
2. Compile the code using `gcc`:

```bash
gcc Slightly_Accelerated_Particle_Collision_Simulation.c -o Particle_Simulation -lSDL2 -lm
```

3. Run the simulation:

```bash
./Particle_Simulation
```

## 🎮 Controls
- **Mouse Movement:** Move the light source by dragging the mouse.
- **Quit:** Close the window or press `Ctrl+C`.

## 📊 Customization
You can adjust the following constants for better performance or visualization:

- `RAYS_NUMBER` — Number of rays (higher = smoother but slower)
- `MAX_SHADOWS` — Maximum number of shadow-casting objects
- Circle properties (position, radius) are customizable in the `main()` function.

## 📸 Example Output
The simulation dynamically traces rays and displays shadows cast by multiple moving circles:

![Simulation Screenshot](example.png)

## 🧠 How It Works
1. Initializes SDL2 window and surface.
2. Generates rays from a moving light source.
3. Checks for intersections with circular obstacles.
4. Renders dynamic light intensity and shadows.
5. Updates the screen continuously.

## 📘 References
- Ray-Circle Intersection: https://mathworld.wolfram.com/Circle-LineIntersection.html
- SDL2 Documentation: https://wiki.libsdl.org/

## 🛠️ Future Improvements
- Implement multiple light sources.
- Add user-controlled obstacle manipulation.
- Improve performance with optimized ray sampling.

## 📜 License
This project is open-source under the MIT License.

Contributions and suggestions are welcome!

