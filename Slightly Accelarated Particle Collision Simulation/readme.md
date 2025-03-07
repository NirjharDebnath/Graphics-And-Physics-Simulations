# 🎈 Particle Collision Simulation – Ideal Gas Behavior Approximation  

This project simulates **particle dynamics** under the influence of **gravity** while interacting through **elastic collisions**. It visualizes the behavior of **ideal gas molecules**, where particles move freely, collide elastically, and obey the laws of **conservation of momentum** and **kinetic energy**.

---

## 📜 Overview
This C-based simulation uses **SDL2** to render bouncing particles affected by gravity. The motion of particles resembles **molecular motion** in an ideal gas. Particles collide elastically with walls and each other, preserving energy while introducing minor randomness to simulate real-world imperfections.

---

## 📊 Features
- 🟢 **Real-Time Particle Simulation**: Particles fall under gravity and exhibit elastic collisions.  
- 🔵 **Elastic Collisions**: Implemented using **conservation laws** and random perturbations for realistic behavior.  
- 🔴 **Boundary Handling**: Particles bounce off the walls, respecting **coefficients of restitution**.  
- 🟡 **Dynamic Particle Creation**: Add particles using **mouse movements**.  
- 🟠 **Color Variation**: Each particle is generated with a **random color**.  
- 🟣 **High Performance**: Efficient handling with **~1000 FPS** via SDL2.  

---

## 📐 Mathematical Model

### 🟢 1. Gravity Calculation
Each particle accelerates downward due to gravity:

$$
v_y = v_y + a \cdot \Delta t
$$

Where:

- v_y = vertical velocity  
- a = 9.8 \, m/s^2 (gravity)  
- \Delta t = 0.001 (time step)  

---

### 🔵 2. Elastic Collision Handling
When two particles collide, their velocities are updated using **1D elastic collision equations**:

For particles A and B, let:

- m_1, m_2 = masses of the particles  
- v_1, v_2 = velocities before collision  
- v_1', v_2' = velocities after collision  
- e = coefficient of restitution  

$$
v_1' = v_2 + e \cdot (v_1 - v_2)
$$

$$
v_2' = v_1 + e \cdot (v_2 - v_1)
$$

Random perturbations are added to simulate thermal agitation.

---

### 🟡 3. Collision Detection
For every pair of particles:

If the distance d between centers is smaller than the sum of their radii (r_1 + r_2):

$$
d = \sqrt{(x_1 - x_2)^2 + (y_1 - y_2)^2}
$$

The particles are overlapping, and their velocities are adjusted.

---

### 🔴 4. Boundary Conditions
Particles reflect elastically when hitting the walls:

$$
v_x' = -e \cdot v_x \quad \text{or} \quad v_y' = -e \cdot v_y
$$

---
Here is the complete README.md content for your particle collision simulation:

# 🎈 Particle Collision Simulation – Ideal Gas Behavior Approximation  

This project simulates **particle dynamics** under the influence of **gravity** while interacting through **elastic collisions**. It visualizes the behavior of **ideal gas molecules**, where particles move freely, collide elastically, and obey the laws of **conservation of momentum** and **kinetic energy**.

---

## 📜 Overview
This C-based simulation uses **SDL2** to render bouncing particles affected by gravity. The motion of particles resembles **molecular motion** in an ideal gas. Particles collide elastically with walls and each other, preserving energy while introducing minor randomness to simulate real-world imperfections.

---

## 📊 Features
- 🟢 **Real-Time Particle Simulation**: Particles fall under gravity and exhibit elastic collisions.  
- 🔵 **Elastic Collisions**: Implemented using **conservation laws** and random perturbations for realistic behavior.  
- 🔴 **Boundary Handling**: Particles bounce off the walls, respecting **coefficients of restitution**.  
- 🟡 **Dynamic Particle Creation**: Add particles using **mouse movements**.  
- 🟠 **Color Variation**: Each particle is generated with a **random color**.  
- 🟣 **High Performance**: Efficient handling with **~1000 FPS** via SDL2.  

---

## 📐 Mathematical Model

### 🟢 1. Gravity Calculation
Each particle accelerates downward due to gravity:

$$
v_y = v_y + a \cdot \Delta t
$$

Where:

- v_y = vertical velocity  
- a = 9.8 \, m/s^2 (gravity)  
- \Delta t = 0.001 (time step)  

---

### 🔵 2. Elastic Collision Handling
When two particles collide, their velocities are updated using **1D elastic collision equations**:

For particles A and B, let:

- m_1, m_2 = masses of the particles  
- v_1, v_2 = velocities before collision  
- v_1', v_2' = velocities after collision  
- e = coefficient of restitution  

$$
v_1' = v_2 + e \cdot (v_1 - v_2)
$$

$$
v_2' = v_1 + e \cdot (v_2 - v_1)
$$

Random perturbations are added to simulate thermal agitation.

---

### 🟡 3. Collision Detection
For every pair of particles:

If the distance d between centers is smaller than the sum of their radii (r_1 + r_2):

$$
d = \sqrt{(x_1 - x_2)^2 + (y_1 - y_2)^2}
$$

The particles are overlapping, and their velocities are adjusted.

---

### 🔴 4. Boundary Conditions
Particles reflect elastically when hitting the walls:

$$
v_x' = -e \cdot v_x \quad \text{or} \quad v_y' = -e \cdot v_y
$$

---

## 📦 Project Structure

├── gravity_simulation.c   # Main simulation source code └── README.md              # This file

---

## 🛠️ Requirements
Ensure the following are installed:

- **GCC** (GNU Compiler Collection)  
- **SDL2** development library  

---

## 🚀 Installation & Execution

1. **Install SDL2** (Linux-based systems):
```bash
sudo apt-get install libsdl2-dev
```
2. Compile the program:


```bash
gcc gravity_simulation.c -o gravity_sim -lm -lSDL2
```
3. Run the simulation:


```bash
./gravity_sim
```

---

## 🖱️ Controls


---

## 📊 Simulation Parameters


---

## 📸 Sample Output

Particles bounce off the walls and interact elastically:

Colors represent individual molecules.

Gravity pulls particles down.

Elastic collisions mimic ideal gas dynamics.



---

## 🧠 Concepts Demonstrated

1. **Ideal Gas Approximation** – Simulates free-moving particles with elastic collisions.


2. **Elastic Collisions** – Conservation of momentum and kinetic energy.


3. **Boundary Reflection** – Coefficient of restitution ensures energy retention.


4. **Dynamic Memory Allocation** – Handles an expanding array of particles.




---

## 📚 Further Improvements

📊 **Add Thermodynamic Properties** – Measure pressure, temperature, and volume.

🔄 **Speed Control** – Adjustable simulation speeds.

🔥 **Advanced Collisions** – Implement inelastic collisions and more complex forces.



---

## 📖 References

1. **Ideal Gas Law**: Wikipedia - Ideal Gas Law


2. **Elastic Collisions**: Wikipedia - Elastic Collision


3. **SDL2 Documentation**: SDL2 Official Docs




---

## 🧑‍💻 Happy Simulating!

This is a comprehensive README with proper LaTeX math equations, technical details, and clear instructions. Let me know if you'd like any other enhancements!

now if you'd like more enhancements or additional features!

