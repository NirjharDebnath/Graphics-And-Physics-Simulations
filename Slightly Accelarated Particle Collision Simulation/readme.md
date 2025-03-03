# Gravity-Based Particle Simulation

This project is a **real-time gravity-based particle simulation** implemented in **C** using the **SDL2** library. It simulates the motion of particles under the influence of gravity, incorporating collision detection and restitution mechanics. The simulation creates new particles based on mouse movements, making it interactive and visually dynamic.

---

## 📖 Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Technical Details](#technical-details)
  - [Particle Structure](#particle-structure)
  - [Gravity and Motion](#gravity-and-motion)
  - [Collision Detection](#collision-detection)
- [Installation and Usage](#installation-and-usage)
- [Code Walkthrough](#code-walkthrough)
- [Customization](#customization)
- [Future Enhancements](#future-enhancements)

---

## 📝 Introduction

This simulation models the behavior of circular particles under gravity. The particles fall, bounce off walls, and interact with other particles through elastic collisions. The simulation is designed for real-time execution and utilizes **SDL2** for rendering and event handling.

---

## ✨ Features

- **Gravity Simulation**: Particles accelerate downwards under constant gravity.
- **Elastic Collisions**: Particles collide with each other and bounce off.
- **Boundary Handling**: Particles reflect when they hit the edges of the window.
- **Random Colors**: Each particle is rendered in a randomly assigned color.
- **Dynamic Creation**: Particles are generated at the mouse pointer's position.

---

## 🛠️ Technical Details

### 📊 Particle Structure

Each particle is represented using the following structure:

```c
struct Circle {
    double m;         // Mass of the particle
    double x, y;     // Position coordinates
    double r;       // Radius of the particle
    double velocity_x, velocity_y; // Velocity components
    Uint8 red, green, blue, a; // Color (RGBA)
};
```

### 📈 Gravity and Motion

Particles experience a constant downward acceleration due to gravity:

```c
double acceleration = Gravity * 0.001;
```

The position is updated using basic kinematics:

```c
circles[i].velocity_y += acceleration;
circles[i].y += circles[i].velocity_y;
circles[i].x += circles[i].velocity_x;
```

### 🔄 Collision Detection

The simulation detects and resolves particle-particle collisions using the following approach:

1. **Distance Calculation**: If the distance between two particles is less than their combined radii, a collision occurs.

```c
double distance = sqrt(dx * dx + dy * dy);
if (distance < circles[i].r + circles[j].r) { ... }
```

2. **Collision Response**: The velocities are updated based on the coefficient of restitution (elasticity).

```c
double vi_new = vj + e * (vi - vj);
```

3. **Overlap Resolution**: Particles are pushed apart to prevent overlapping.

```c
double overlap = (circles[i].r + circles[j].r) - distance;
```

---

## 📦 Installation and Usage

### Prerequisites

- **SDL2** installed on your system.

### Compilation

Ensure **SDL2** is installed and use the following command to compile the code:

```bash
gcc gravity_simulation.c -o gravity_simulation -lSDL2 -lm
```

### Run the Simulation

```bash
./gravity_simulation
```

---

## 📚 Code Walkthrough

1. **Initialization**: Sets up SDL2 window and renderer.
2. **Particle Generation**: Particles are created when the mouse moves.
3. **Physics Simulation**: Updates positions, applies gravity, handles collisions.
4. **Rendering**: Draws the grid (optional) and particles.
5. **Event Handling**: Captures SDL events (e.g., window close, mouse movement).

---

## 🔧 Customization

You can tweak the following parameters for different behaviors:

| Parameter                 | Description                       | Default Value |
|---------------------------|-----------------------------------|---------------|
| `Gravity`                 | Gravitational acceleration        | `9.8`        |
| `CELL_SIZE`               | Size of the grid cells            | `20`         |
| `RADIUS`                  | Radius of particles               | `4`          |
| `COEFF_OF_RESTITUTION`    | Elasticity of collisions (0-1)    | `0.8`        |
| `VELOCITY_X`, `VELOCITY_Y`| Initial velocity of particles     | `0.0`        |

---

## 🚀 Future Enhancements

- **Performance Optimization**: Improve collision detection efficiency.
- **Mouse Interaction**: Allow clicking to add or drag particles.
- **Particle Properties**: Support for different masses and sizes.
- **Visualization**: Display particle trails and energy graphs.

---

## 📄 License

Feel free to use, modify, and share this project under the **MIT License**.

---

## 🧑‍💻 Contributions

Contributions are welcome! Fork this repository, submit issues, or create pull requests.

---

## 📬 Contact

For questions or feedback, feel free to reach out!

Enjoy simulating! 🎮


