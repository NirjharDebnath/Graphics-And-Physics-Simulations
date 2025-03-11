# 🎵 Simple Harmonic Motion (SHM) Simulation with SDL2

![SHM Simulation](https://img.shields.io/badge/SDL2-C%2B%2B-blue.svg) ![License](https://img.shields.io/badge/license-MIT-green.svg) ![Physics](https://img.shields.io/badge/Physics-SHM-orange)

A **Simple Harmonic Motion (SHM)** simulation using **C++** and **SDL2**, visualizing oscillating particles in real time with adjustable parameters. This project demonstrates the physics of SHM and how multiple oscillators interact in a continuous wave-like motion.

---

## 📽️ Demo Preview

- ![SHM Simulation Demo](https://github.com/NirjharDebnath/Graphics_And_Physics_Simulations/blob/main/Simple%20Harmonic%20Motion%20Simulation/SHM_video.mp4)
  
*Watch the beautiful oscillation in action!*

---

## 📚 Understanding the Physics Behind SHM

### 🔢 SHM Equation:

Simple Harmonic Motion is governed by the following equation:

$$
y(t) = A \times \sin(\omega t + \phi)
$$

Where:
- \( y(t) \) → Position at time \( t \)
- \( A \) → Amplitude (Maximum displacement from equilibrium)
- \( $\omega$ \) → Angular frequency \( $\omega$ = 2 $\pi$ f \)
- \( $\phi$ \) → Phase offset (Initial position in the oscillation cycle)

---

### 📊 Parameters Used:
- **Amplitude (A)**: Controls how far each point moves from the equilibrium line.
- **Angular Frequency (ω)**: Determines the speed of oscillation.
- **Phase Offset (ϕ)**: Staggers the oscillation to create a wave pattern.

---

## 🛠️ Features
✅ Real-time SHM visualization with **SDL2**  
✅ Customizable parameters for amplitude, frequency, and phase offset  
✅ Smooth motion with high FPS rendering  
✅ Dynamic wave connection between oscillators  
✅ Circular motion representation of SHM origin  

---

## 🧑‍💻 Technical Implementation

### 🔍 Core Components:
1. **Oscillating Particles**: Each particle follows the SHM equation to update its position.
2. **Circular Motion**: Displays the projection of SHM from circular motion.
3. **Grid System**: Helps visualize the motion in Cartesian space.
4. **Performance Optimization**: Ensures smooth animations by controlling frame delay.

### 🗂️ Key Functions:
```cpp
void draw_shape(SDL_Renderer *renderer, int x, int y, SDL_Color color);
void draw_point(SDL_Renderer *renderer, int x, int y);
void draw_grid(SDL_Renderer *renderer);
void FillCircle_Outline(SDL_Renderer *renderer, struct Circle circle, SDL_Color color);
```
🚀 Getting Started
🧰 Prerequisites
Ensure you have SDL2 installed on your system.

For Ubuntu:

```bash
sudo apt update
sudo apt install libsdl2-dev
```
For Windows: Download and install SDL2 from SDL2 Downloads.

📥 Clone the Repository
```bash
git clone https://github.com/your-username/Simple Harmonic Motion Simulation.git
cd Simple Harmonic Motion Simulation
```
🛠️ Build and Run
```bash
g++ SHM.cpp -o SHM -lSDL2 -lm
./SHM
```
🎮 Controls and Customization
You can modify the simulation by tweaking the following parameters in the code:

```cpp
#define HEIGHT 400
#define WIDTH 1600
#define BODY_SIZE 10
#define SHM_POINT_SIZE 20
#define CELL_SIZE 40
#define NUM_BODIES (1000/CELL_SIZE - 1)

double amplitude = 160;      // Maximum displacement
double omega = -0.05;        // Angular frequency
```
📊 Output Example

Grid + SHM Wave: Displays the oscillating bodies along a horizontal axis.
Circular Motion: Shows the origin circle representing SHM projection.
Wave Connection: Connects SHM particles in a continuous wave.
📸 Screenshots
![SHM Simulation Image](https://github.com/NirjharDebnath/Graphics_And_Physics_Simulations/blob/main/Simple%20Harmonic%20Motion%20Simulation/SHM_image.png)

Circular Projection of SHM

Waveform of Oscillating Bodies

**📜 License**
- This project is licensed under the MIT License. Feel free to use and modify it!

**🤝 Contributing**
- Contributions are welcome! Feel free to open issues or pull requests to improve the simulation.

**📧 Contact**
- If you have any questions, feel free to reach out:

GitHub: github.com/NirjharDebnath

⭐ If you liked this project, give it a star! ⭐

---






