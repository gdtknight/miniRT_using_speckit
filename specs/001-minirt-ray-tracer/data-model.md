# Data Models: MiniRT Ray Tracer

This document defines the core C data structures (`structs`) for the miniRT project.

## Core Data Types

```c
// Represents a 3D vector or a color (R,G,B)
typedef struct s_vec3 {
    double x;
    double y;
    double z;
} t_vec3;

// Represents a ray with an origin and a direction
typedef struct s_ray {
    t_vec3 origin;
    t_vec3 direction;
} t_ray;
```

## Scene Elements

```c
// Represents the camera
typedef struct s_camera {
    t_vec3  position;
    t_vec3  orientation;
    int     fov;
} t_camera;

// Represents a light source (ambient or point)
typedef struct s_light {
    t_vec3  position; // Not used by ambient light
    double  ratio;
    t_vec3  color;
    struct s_light *next;
} t_light;

// Represents a generic object that can be intersected
typedef struct s_object {
    void    *object; // Pointer to the specific object struct (e.g., t_sphere)
    int     type; // Enum/define for SPHERE, PLANE, CYLINDER
    t_vec3  color;
    // Material properties for reflection, etc., can be added here
    struct s_object *next;
} t_object;
```

## Geometric Objects

```c
// Represents a sphere
typedef struct s_sphere {
    t_vec3  center;
    double  radius;
} t_sphere;

// Represents a plane
typedef struct s_plane {
    t_vec3  point;
    t_vec3  normal;
} t_plane;

// Represents a cylinder
typedef struct s_cylinder {
    t_vec3  center;
    t_vec3  axis; // Normalized direction vector
    double  diameter;
    double  height;
} t_cylinder;
```

## Scene Container

```c
// Top-level struct to hold all scene information
typedef struct s_scene {
    t_camera    camera;
    t_light     *lights;
    t_object    *objects;
    t_light     *ambient_light;
} t_scene;
```
