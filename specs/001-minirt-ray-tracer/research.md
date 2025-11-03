# Research & Decisions: MiniRT Ray Tracer

## Ray-Object Intersection Formulas

- **Decision**: Standard algebraic solutions will be used for all ray-object intersection tests.
- **Rationale**: These methods are efficient, well-documented, and provide exact solutions.

### Ray-Sphere Intersection

- **Formula**: Solved by finding the roots of a quadratic equation derived from the sphere equation `||P - C||^2 = r^2` and the ray equation `P = O + tD`.

### Ray-Plane Intersection

- **Formula**: Solved by substituting the ray equation into the plane equation `(P - P0) . n = 0` and solving for the parameter `t`.

### Ray-Cylinder Intersection

- **Formula**: A more complex calculation involving solving a quadratic equation for the infinite cylinder body and then checking if the intersection points lie within the cylinder's height bounds. Intersections with the end caps are handled as ray-plane intersections.

## Lighting Model

- **Decision**: The Phong lighting model will be implemented.
- **Rationale**: It is a simple yet effective model that provides good visual results by combining ambient and diffuse components, which is sufficient for the project's requirements.

- **Components**:
  - **Ambient**: `I_ambient = color_light_ambient * K_a` (where `K_a` is the object's ambient reflection coefficient, assumed to be its color).
  - **Diffuse**: `I_diffuse = color_light * K_d * (L . N)` (where `K_d` is the object's diffuse reflection coefficient, `L` is the light vector, and `N` is the surface normal).

## Scene File Format

- **Decision**: A simple, space-delimited text format will be used for `.rt` files.
- **Rationale**: This is the standard for the miniRT project. It is easy to parse and human-readable.
- **Details**: The specific syntax for each element (`A`, `C`, `L`, `sp`, `pl`, `cy`) will be documented in the `contracts/` directory.
