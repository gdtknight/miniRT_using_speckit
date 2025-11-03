# Feature Specification: MiniRT Ray Tracer Implementation

**Feature Branch**: `001-minirt-ray-tracer`  
**Created**: 2025-11-03  
**Status**: Draft  
**Input**: User description: "42의 miniRT subject 를 실제로 구현하는 프로젝트를 진행할거야. 이 프로젝트의 목적은 기초적인 Ray Tracing Algorithm 을 C Language 로 구현하는 것이야."

## User Scenarios & Testing *(mandatory)*

### User Story 1 - Render Basic Scene with Simple Objects (Priority: P1)

As a user, I want to define a scene with a camera, lights, and simple geometric objects (planes, spheres) in a `.rt` file, so that the program can render it into a static image.

**Why this priority**: This is the core functionality of the ray tracer. It establishes the rendering pipeline and object intersection system.

**Independent Test**: The program can be run with a `.rt` file containing only spheres and planes. The output image should correctly represent the scene, object colors, and basic lighting.

**Acceptance Scenarios**:

1.  **Given** a `.rt` file describing a scene with one sphere and one plane, **When** the program is executed with this file, **Then** it produces an image file showing the sphere and plane from the camera's perspective.
2.  **Given** a `.rt` file with invalid syntax, **When** the program is executed, **Then** it prints a descriptive error message and exits gracefully.

---

### User Story 2 - Add Support for Complex Objects (Priority: P2)

As a user, I want to add cylinders to the scene description file, so that I can render more complex scenes.

**Why this priority**: Extends the object-oriented structure of the program and adds a more complex intersection calculation, which is a key requirement of the project.

**Independent Test**: The program can be run with a `.rt` file containing cylinders. The output image should correctly render the cylinders, including their caps, and handle lighting on their curved and flat surfaces.

**Acceptance Scenarios**:

1.  **Given** a `.rt` file describing a scene with one cylinder, **When** the program is executed, **Then** it produces an image file correctly showing the cylinder.
2.  **Given** a scene with intersecting objects including a cylinder, **When** the program renders the scene, **Then** the intersections are calculated correctly and the closer object is visible.

---

### User Story 3 - Implement Realistic Lighting and Shadows (Priority: P3)

As a user, I want the rendered image to show realistic lighting effects, including ambient light, point lights, and shadows.

**Why this priority**: Shadows and multiple light sources dramatically increase the realism of the rendered image and are fundamental to a ray tracing algorithm.

**Independent Test**: A scene with objects positioned to cast shadows can be rendered. The output image should show hard shadows in the correct places, and object colors should be influenced by both ambient and point light sources.

**Acceptance Scenarios**:

1.  **Given** a scene with a point light and an object between the light and another surface, **When** the scene is rendered, **Then** a shadow of the object is cast on the surface.
2.  **Given** a scene with an ambient light and a point light, **When** the scene is rendered, **Then** all parts of the objects are visible (due to ambient light) and parts facing the point light are brighter.

---

### Edge Cases

-   **Parsing**: How does the system handle `.rt` files with missing, extra, or malformed parameters for objects, lights, or the camera?
-   **Rendering**: What happens if a light source is inside an object?
-   **Rendering**: How are objects with no light source rendered (should be black or influenced by ambient light)?
-   **Performance**: How does the system handle very large or complex scenes? (Though performance is not a primary goal, it should be reasonably efficient).

## Requirements *(mandatory)*

### Functional Requirements

-   **FR-001**: The system MUST parse scene description files with a `.rt` extension.
-   **FR-002**: The system MUST support the following geometric objects: Sphere (`sp`), Plane (`pl`), and Cylinder (`cy`).
-   **FR-003**: The system MUST support a camera definition (`C`) that specifies its position, orientation vector, and field of view (FOV).
-   **FR-004**: The system MUST support an ambient light source (`A`) with a specified color and intensity.
-   **FR-005**: The system MUST support point light sources (`L`) with a specified position, color, and intensity.
-   **FR-006**: The system MUST calculate object intersections using ray tracing to determine which object is visible at each pixel.
-   **FR-007**: The system MUST implement a lighting model that includes ambient and diffuse components.
-   **FR-008**: The system MUST calculate hard shadows by tracing a ray from the intersection point to each light source.
-   **FR-009**: The system MUST output the rendered image to a file (e.g., in BMP format) or display it in a window using the `miniLibX` library.
-   **FR-010**: The system MUST handle errors in the `.rt` file gracefully and output a clear error message.

### Key Entities *(include if feature involves data)*

-   **Scene**: A container for all objects, lights, and the camera. Defined in the `.rt` file.
-   **Camera**: Defines the viewpoint from which the scene is rendered. Has attributes for position, orientation, and FOV.
-   **Light**: Represents a light source. Can be Ambient or Point light. Has attributes for color and intensity.
-   **Object**: A geometric shape in the scene. Can be a Sphere, Plane, or Cylinder. Has attributes for position, size, color, and orientation.

## Success Criteria *(mandatory)*

### Measurable Outcomes

-   **SC-001**: The program successfully renders all provided valid example `.rt` files, with output images matching the visual examples in the project subject.
-   **SC-002**: The program rejects 100% of provided invalid `.rt` files and returns a descriptive, human-readable error message.
-   **SC-003**: The program must run without memory leaks, verifiable with memory-checking tools (e.g., Valgrind).
-   **SC-004**: All implemented geometric shapes (Sphere, Plane, Cylinder) and lighting effects (Ambient, Point, Shadows) must be visually correct according to ray tracing principles.