# Implementation Plan: MiniRT Ray Tracer

**Feature Spec**: [spec.md](./spec.md)

## Technical Context

- **Programming Language**: C (C99 standard)
- **Graphics Library**: `miniLibX` (as required by the 42 curriculum for this project)
- **Compiler**: `gcc` with standard flags (`-Wall`, `-Wextra`, `-Werror`)
- **Build System**: `Makefile`
- **Key Algorithms**:
  - Ray-Object Intersection (Sphere, Plane, Cylinder)
  - Phong Lighting Model (Ambient, Diffuse)
  - Hard Shadows
- **Dependencies**: None outside of standard C libraries and `miniLibX`.

## Constitution Check

- **I. Library-First**: The project will be structured into modular libraries:
  - `libvec`: For vector and matrix math.
  - `libft`: Standard utility functions (as is common in 42 projects).
  - `parser`: For `.rt` file parsing.
  - `renderer`: Core ray tracing and rendering logic.
- **II. CLI Interface**: The final executable will be a CLI tool that accepts a `.rt` file as an argument.
- **III. Test-First**: A TDD approach is recommended. Unit tests should be created for the math library, parser, and intersection functions before implementation.
- **IV. Integration Testing**: Integration tests will involve rendering a suite of test scenes and comparing the output to known-correct images.

## Phase 0: Outline & Research

**Artifacts**: [research.md](./research.md)

- **Task 1**: Document the mathematical formulas for ray-sphere, ray-plane, and ray-cylinder intersections.
- **Task 2**: Document the Phong lighting model equations (ambient, diffuse).
- **Task 3**: Define the structure of the `.rt` scene description file format.

## Phase 1: Design & Contracts

**Artifacts**:
- [data-model.md](./data-model.md)
- [contracts/rt-file-format.md](./contracts/rt-file-format.md)
- [quickstart.md](./quickstart.md)

- **Task 1**: Define the C `structs` for vectors, colors, rays, camera, lights, and all geometric objects.
- **Task 2**: Formally document the `.rt` file syntax and all valid identifiers (`A`, `C`, `L`, `sp`, `pl`, `cy`) in the contracts directory.
- **Task 3**: Create a `Makefile` structure for compiling the libraries and the final executable.
- **Task 4**: Write a `quickstart.md` explaining how to compile and run the project.

## Phase 2: Implementation & Testing

**Artifacts**: `src/`, `include/`, `tests/`

This phase is for the actual implementation and is beyond the scope of this planning command.