# Gravity Ball Simulation: Physics Intuition and Formulas 🎮🌍

This project simulates the behavior of multiple balls under the influence of gravity, resembling the nature of an ideal gas. Below is a detailed explanation of the physics behind the simulation, including key formulas and their intuition.

---

## 📌 1. Gravity and Motion

### Gravitational Acceleration

Each ball experiences a constant gravitational acceleration:

\(
g = 9.8 \, \(text{m/s}^2\)
\)

In the simulation, this is scaled down by a factor of 0.001 for smoother motion:

\[
a_y = g \cdot 0.001
\]

### Velocity Update

The velocity of each ball is updated every frame based on acceleration:

\[
v_y = v_y + a_y \cdot \Delta t
\]

Where:
- \( v_y \) = vertical velocity
- \( \Delta t \) = time step (based on frame rate)

### Position Update

The position is updated using the velocity:

\[
y = y + v_y \cdot \Delta t, \quad x = x + v_x \cdot \Delta t
\]

---

## 💥 2. Elastic Collisions

### Collision Detection

Collisions between two balls are detected when the distance between their centers is less than the sum of their radii:

\[
\text{distance} = \sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2} < (r_1 + r_2)
\]

### Resolving Overlap

To prevent balls from overlapping, they are moved apart along the collision axis:

\[
\text{overlap} = (r_1 + r_2) - \text{distance}
\]

Balls are adjusted by half the overlap:

\[
x_1 = x_1 + \frac{\text{overlap}}{2} \cdot \cos(\theta), \quad y_1 = y_1 + \frac{\text{overlap}}{2} \cdot \sin(\theta)
\]

Where:

\[
\theta = \arctan2(y_2 - y_1, x_2 - x_1)
\]

### Velocity Update After Collision

Using the conservation of momentum and coefficient of restitution \( e \):

\[
v_{\text{rel}} = (v_{x2} - v_{x1}) \cdot n_x + (v_{y2} - v_{y1}) \cdot n_y
\]

New velocities:

\[
v_{x1}' = v_{x1} + (1 + e) \cdot \frac{m_2}{m_1 + m_2} \cdot v_{\text{rel}} \cdot n_x
\]
\[
v_{y1}' = v_{y1} + (1 + e) \cdot \frac{m_2}{m_1 + m_2} \cdot v_{\text{rel}} \cdot n_y
\]
\[
v_{x2}' = v_{x2} - (1 + e) \cdot \frac{m_1}{m_1 + m_2} \cdot v_{\text{rel}} \cdot n_x
\]
\[
v_{y2}' = v_{y2} - (1 + e) \cdot \frac{m_1}{m_1 + m_2} \cdot v_{\text{rel}} \cdot n_y
\]

Where:
- \( m_1 \) and \( m_2 \) = masses of the balls
- \( e \) = coefficient of restitution (set to 0.8)

---

## 🛑 3. Boundary Collisions

When a ball collides with the simulation boundary, its velocity is reversed and scaled by the coefficient of restitution \( e \):

### Horizontal Boundaries:

\[
v_x = -e \cdot v_x
\]

### Vertical Boundaries:

\[
v_y = -e \cdot v_y
\]

Position is clamped to stay within bounds:

\[
x = \text{clamp}(x, r, \text{WIDTH} - r), \quad y = \text{clamp}(y, r, \text{HEIGHT} - r)
\]

---

## 🧠 4. Intuition Behind the Simulation

- **Gravity**: Balls accelerate downward, simulating the real-world effect of gravity.
- **Elastic Collisions**: Collisions conserve energy and momentum, imitating ideal gas behavior.
- **Boundary Collisions**: Walls act as elastic barriers, keeping the balls within the simulation area.

---

## ⚙️ 5. Key Parameters

- **Gravity (\( g \))**: \( 9.8 \, \text{m/s}^2 \) (scaled down by 0.001).
- **Coefficient of Restitution (\( e \))**: 0.8 (controls the bounciness of collisions).
- **Ball Radius (\( r \))**: 4 pixels.
- **Initial Velocities**: \( v_x = 0.0 \), \( v_y = 0.0 \).

---

## 🚀 6. Future Enhancements

- **Air Resistance**: Simulate drag forces proportional to velocity.
- **Friction**: Model energy loss to slow down balls over time.
- **User Interaction**: Allow real-time adjustment of gravity, restitution, and other parameters.

---

## 📖 Getting Started

1. Clone the repository:

```bash
git clone https://github.com/yourusername/gravity-ball-simulation.git
cd gravity-ball-simulation
```

2. Run the simulation (assuming SDL2):

```bash
make
./gravity_sim
```

---

## 📊 Contributing

Contributions are welcome! Feel free to fork the repository and submit pull requests with improvements or new features.

---

## 📄 License

This project is licensed under the MIT License. Feel free to use and modify it.

---

Enjoy experimenting with gravity and elastic collisions in this dynamic simulation! 🎉
