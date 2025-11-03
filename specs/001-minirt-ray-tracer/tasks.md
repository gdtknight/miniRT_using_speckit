# Actionable Tasks: MiniRT Ray Tracer

**Implementation Strategy**: The feature will be developed incrementally, with each user story representing a deliverable, independently testable milestone. The MVP is User Story 1.

## Phase 1: Project Setup

- [X] T001 Create the project directory structure: `src/`, `include/`, `lib/`, `scenes/`, `tests/`
- [X] T002 Create a basic `Makefile` to compile the project.
- [X] T003 Set up the `miniLibX` library.
- [X] T004 Create the main entry point file `src/main.c`.

## Phase 2: Foundational Libraries

- [X] T005 [P] Create the vector library header `include/vec3.h` with function declarations for vector operations (add, subtract, dot product, cross product).
- [X] T006 [P] Implement the vector library functions in `src/lib/vec3/`.
- [X] T007 [P] Create unit tests for the vector library in `tests/test_vec3.c`.
- [X] T008 [P] Create a utility library header `include/libft.h` for common functions (e.g., string manipulation, memory allocation).
- [X] T009 [P] Implement the utility library in `src/lib/libft/`.

## Phase 3: User Story 1 - Render Basic Scene

**Goal**: Render a scene with spheres and planes.
**Independent Test**: The program can render a `.rt` file with spheres and planes, and handle parsing errors.

- [X] T010 [US1] Define all core data structures from `data-model.md` in `include/minirt.h`.
- [X] T011 [US1] Implement the `.rt` file parser for scene-wide elements (Ambient light `A`, Camera `C`) in `src/parser/parser.c`.
- [X] T012 [US1] Implement the parser for basic objects (Sphere `sp`, Plane `pl`) in `src/parser/parse_objects.c`.
- [X] T013 [US1] Create unit tests for the parser in `tests/test_parser.c`.
- [X] T014 [US1] Implement the ray generation logic based on camera position and FOV in `src/renderer/ray.c`.
- [X] T015 [US1] Implement the intersection logic for spheres in `src/renderer/intersect_sphere.c`.
- [X] T016 [US1] Implement the intersection logic for planes in `src/renderer/intersect_plane.c`.
- [ ] T017 [US1] Implement the main rendering loop in `src/renderer/render.c` that iterates through pixels and finds the closest object.
- [ ] T018 [US1] Implement a simple lighting model (ambient + diffuse) in `src/renderer/lighting.c`.
- [ ] T019 [US1] Integrate `miniLibX` to display the rendered image in a window in `src/mlx_utils.c`.

## Phase 4: User Story 2 - Add Support for Cylinders

**Goal**: Render scenes containing cylinders.
**Independent Test**: The program can render a `.rt` file containing cylinders correctly.

- [ ] T020 [US2] Add the cylinder parsing logic to the parser in `src/parser/parse_objects.c`.
- [ ] T021 [US2] Create unit tests for cylinder parsing in `tests/test_parser.c`.
- [ ] T022 [US2] Implement the intersection logic for cylinders (body and caps) in `src/renderer/intersect_cylinder.c`.
- [ ] T023 [US2] Create unit tests for cylinder intersection in `tests/test_intersections.c`.
- [ ] T024 [US2] Update the main rendering loop to include cylinders in the object list.

## Phase 5: User Story 3 - Implement Realistic Lighting and Shadows

**Goal**: Add shadows to the rendered scene.
**Independent Test**: A scene with objects casting shadows is rendered correctly.

- [ ] T025 [US3] Modify the lighting calculation in `src/renderer/lighting.c` to include a shadow check.
- [ ] T026 [US3] Implement the shadow ray logic: for each intersection, cast a ray towards each light source to check for occluding objects.
- [ ] T027 [US3] Create a test scene in `scenes/shadow_test.rt` to validate shadow rendering.

## Phase 6: Polish & Cross-Cutting Concerns

- [ ] T028 [P] Review all code for compliance with the 42 norm (`norminette`).
- [ ] T029 [P] Run `valgrind` or other memory analysis tools to check for leaks.
- [ ] T030 Create comprehensive documentation in a `README.md` file.

## Dependencies

- **US1** is the base for all other stories.
- **US2** depends on **US1**.
- **US3** depends on **US1**.

## Parallel Execution

- Within **Phase 2**, the `libvec` and `libft` libraries can be developed in parallel.
- Within **Phase 3 (US1)**, parser development and renderer development can begin in parallel, but the renderer will eventually depend on the parser's output.
