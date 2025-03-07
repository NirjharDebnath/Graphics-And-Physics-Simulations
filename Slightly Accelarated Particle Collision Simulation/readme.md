# Gravity Ball Simulation: Physics Intuition and Formulas 🎮🌍

This project simulates the behavior of multiple balls under the influence of gravity, resembling the nature of an ideal gas. Below, we provide a detailed explanation of the physics behind the simulation, including the key formulas and their intuition.

---

## 1. **Gravity and Motion** 🌍

### Gravitational Acceleration
Each ball is subject to a constant gravitational acceleration \( g = 9.8 \, \text{m/s}^2 \). In the simulation, this is scaled down by a factor of \( 0.001 \) to make the motion visually smooth:

\[
a_y = g \cdot 0.001
\]

Here, \( a_y \) is the vertical acceleration applied to each ball.

### Velocity Update
The velocity of each ball is updated every frame based on the acceleration:

\[
v_y = v_y + a_y \cdot \Delta t
\]

where:
- \( v_y \) is the vertical velocity,
- \( \Delta t \) is the time step (implicitly defined by the frame rate).

### Position Update
The position of each ball is updated using the velocity:

\[
y = y + v_y \cdot \Delta t
\]

Similarly, the horizontal position \( x \) is updated using the horizontal velocity \( v_x \):

\[
x = x + v_x \cdot \Delta t
\]

---

## 2. **Elastic Collisions** 💥

### Collision Detection
Collisions between two balls are detected by checking if the distance between their centers is less than the sum of their radii:

\[
\text{distance} = \sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2} < r_1 + r_2
\]

If this condition is true, the balls are overlapping, and a collision is resolved.

### Resolving Overlap
To resolve the overlap, the balls are moved apart along the line connecting their centers. The overlap distance is:

\[
\text{overlap} = (r_1 + r_2) - \text{distance}
\]

The balls are then moved apart by half the overlap distance:

\[
x_1 = x_1 + \frac{\text{overlap}}{2} \cdot \cos(\theta), \quad y_1 = y_1 + \frac{\text{overlap}}{2} \cdot \sin(\theta)
\]
\[
x_2 = x_2 - \frac{\text{overlap}}{2} \cdot \cos(\theta), \quad y_2 = y_2 - \frac{\text{overlap}}{2} \cdot \sin(\theta)
\]

where \( \theta = \text{atan2}(y_2 - y_1, x_2 - x_1) \) is the angle between the two centers.

### Velocity Update After Collision
The velocities of the balls are updated based on the conservation of momentum and the coefficient of restitution \( e \). The relative velocity along the line of collision is:

\[
v_{\text{rel}} = (v_{x2} - v_{x1}) \cdot n_x + (v_{y2} - v_{y1}) \cdot n_y
\]

where \( n_x = \frac{x_2 - x_1}{\text{distance}} \) and \( n_y = \frac{y_2 - y_1}{\text{distance}} \) are the components of the unit normal vector.

The new velocities are calculated as:

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

Here, \( m_1 \) and \( m_2 \) are the masses of the two balls, and \( e \) is the coefficient of restitution (set to \( 0.8 \) in the simulation).

---

## 3. **Boundary Collisions** 🛑

When a ball collides with the boundaries of the window, its velocity is reversed and scaled by the coefficient of restitution \( e \):

### Horizontal Boundaries
If the ball hits the left or right wall:

\[
v_x = -e \cdot v_x
\]

### Vertical Boundaries
If the ball hits the top or bottom wall:

\[
v_y = -e \cdot v_y
\]

The position of the ball is also adjusted to ensure it stays within the window:

\[
x = \text{clamp}(x, r, \text{WIDTH} - r)
\]
\[
y = \text{clamp}(y, r, \text{HEIGHT} - r)
\]

where \( r \) is the radius of the ball.

---

## 4. **Intuition Behind the Simulation** 🧠

- **Gravity**: The balls accelerate downward, simulating the effect of gravity. This creates a realistic "falling" motion.
- **Elastic Collisions**: The collisions between balls conserve momentum and energy, making the simulation behave like an ideal gas. The coefficient of restitution \( e \) controls how "bouncy" the collisions are.
- **Boundary Collisions**: The walls act as perfectly elastic barriers, ensuring the balls stay within the window.

---

## 5. **Key Parameters** ⚙️

- **Gravity (\( g \))**: \( 9.8 \, \text{m/s}^2 \) (scaled down by \( 0.001 \)).
- **Coefficient of Restitution (\( e \))**: \( 0.8 \) (controls the bounciness of collisions).
- **Ball Radius (\( r \))**: \( 4 \) pixels.
- **Initial Velocities**: \( v_x = 0.0 \), \( v_y = 0.0 \).

---

## 6. **Future Enhancements** 🚀

- **Air Resistance**: Introduce a drag force proportional to the velocity to simulate air resistance.
- **Friction**: Add friction during collisions to make the balls eventually come to rest.
- **User Interaction**: Allow users to adjust parameters like gravity, restitution, and ball size in real-time.

---

This simulation provides a simple yet powerful demonstration of physics principles in action. By understanding the formulas and intuition behind it, you can extend the simulation to include more complex behaviors or use it as a foundation for other physics-based projects. 🎉
