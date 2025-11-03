# API Reference

Complete reference for miniRT's public API.

---

## Vector Operations

### vec3_new
```c
t_vec3 vec3_new(double x, double y, double z);
```
Creates a new 3D vector.

**Parameters:**
- `x`: X component
- `y`: Y component  
- `z`: Z component

**Returns:** New vector

**Example:**
```c
t_vec3 position = vec3_new(0.0, 5.0, -10.0);
```

---

### vec3_add
```c
t_vec3 vec3_add(t_vec3 v1, t_vec3 v2);
```
Adds two vectors.

**Returns:** v1 + v2

---

### vec3_sub
```c
t_vec3 vec3_sub(t_vec3 v1, t_vec3 v2);
```
Subtracts two vectors.

**Returns:** v1 - v2

---

### vec3_mul
```c
t_vec3 vec3_mul(t_vec3 v, double scalar);
```
Multiplies vector by scalar.

**Returns:** v * scalar

---

### vec3_div
```c
t_vec3 vec3_div(t_vec3 v, double scalar);
```
Divides vector by scalar.

**Returns:** v / scalar

---

### vec3_dot
```c
double vec3_dot(t_vec3 v1, t_vec3 v2);
```
Calculates dot product.

**Returns:** v1 · v2

**Use Cases:**
- Angle between vectors: `cos(θ) = dot(v1, v2) / (|v1| * |v2|)`
- Projection calculations
- Checking parallelism

---

### vec3_cross
```c
t_vec3 vec3_cross(t_vec3 v1, t_vec3 v2);
```
Calculates cross product.

**Returns:** v1 × v2 (perpendicular vector)

**Use Cases:**
- Finding perpendicular vectors
- Surface normal calculation
- Coordinate system construction

---

### vec3_length
```c
double vec3_length(t_vec3 v);
```
Calculates vector magnitude.

**Returns:** ||v|| = √(x² + y² + z²)

---

### vec3_normalize
```c
t_vec3 vec3_normalize(t_vec3 v);
```
Normalizes vector to unit length.

**Returns:** v / ||v||

---

## Scene Parsing

### parse_scene
```c
t_scene *parse_scene(char *filename);
```
Parses a `.rt` scene file.

**Parameters:**
- `filename`: Path to scene file

**Returns:**
- Valid `t_scene*` on success
- `NULL` on parse error

**Example:**
```c
t_scene *scene = parse_scene("scenes/simple.rt");
if (!scene)
{
    printf("Error\nFailed to parse scene\n");
    return 1;
}
```

---

### parse_vec3
```c
t_vec3 parse_vec3(char *str);
```
Parses "x,y,z" string to vector.

**Parameters:**
- `str`: Comma-separated coordinates

**Returns:** Parsed vector

---

## Ray Tracing

### get_ray
```c
t_ray get_ray(t_camera camera, int i, int j, int width);
```
Generates ray through pixel.

**Parameters:**
- `camera`: Camera configuration
- `i`: Pixel x-coordinate
- `j`: Pixel y-coordinate
- `width`: Image width

**Returns:** Ray from camera through pixel

---

### intersect_sphere
```c
double intersect_sphere(t_ray ray, t_sphere *sphere);
```
Tests ray-sphere intersection.

**Returns:**
- Distance t if hit (t > 0)
- -1.0 if no hit

---

### intersect_plane
```c
double intersect_plane(t_ray ray, t_plane *plane);
```
Tests ray-plane intersection.

**Returns:**
- Distance t if hit (t > 0)
- -1.0 if no hit

---

### intersect_cylinder
```c
double intersect_cylinder(t_ray ray, t_cylinder *cylinder);
```
Tests ray-cylinder intersection.

**Returns:**
- Distance t if hit (t > 0)
- -1.0 if no hit

---

### find_closest_intersection
```c
t_hit find_closest_intersection(t_scene *scene, t_ray ray);
```
Finds closest object intersection.

**Returns:** Hit information with:
- `t`: Distance to hit
- `point`: Hit position
- `normal`: Surface normal
- `object`: Hit object pointer

---

## Lighting

### calculate_lighting
```c
t_vec3 calculate_lighting(t_scene *scene, t_hit hit);
```
Computes Phong lighting at hit point.

**Returns:** RGB color vector (0-255 range)

**Algorithm:**
1. Start with ambient light
2. For each light source:
   - Calculate diffuse component
   - Calculate specular component
   - Add to accumulated color
3. Clamp to valid range

---

## Rendering

### render_scene
```c
void render_scene(t_scene *scene, t_mlx_data *data);
```
Renders complete scene to image buffer.

**Algorithm:**
```
for each pixel (i, j):
    ray = get_ray(camera, i, j)
    hit = find_closest_intersection(scene, ray)
    if hit:
        color = calculate_lighting(scene, hit)
    else:
        color = background
    set_pixel(i, j, color)
```

---

### vec3_to_color
```c
int vec3_to_color(t_vec3 color);
```
Converts RGB vector to integer color.

**Parameters:**
- `color`: Vector with R,G,B components (0-255)

**Returns:** 32-bit integer (0xRRGGBB format)

---

## MLX Integration

### init_mlx
```c
t_mlx_data *init_mlx(void);
```
Initializes MiniLibX and creates window.

**Returns:**
- `t_mlx_data*` on success
- `NULL` on failure

---

### display_image
```c
void display_image(t_mlx_data *data);
```
Displays rendered image in window.

---

### close_window
```c
int close_window(t_mlx_data *data);
```
Closes window and cleans up.

---

### handle_key
```c
int handle_key(int keycode, t_mlx_data *data);
```
Handles keyboard events.

**Supported Keys:**
- ESC (53): Exit program

---

## BMP Export

### save_to_bmp
```c
void save_to_bmp(t_mlx_data *data, char *filename);
```
Exports rendered image to BMP file.

**Parameters:**
- `data`: MLX image data
- `filename`: Output file path

**Format:** 24-bit BMP (no compression)

**Example:**
```c
save_to_bmp(data, "output.bmp");
```

---

## Data Structures

### t_vec3
```c
typedef struct s_vec3
{
    double  x;
    double  y;
    double  z;
}   t_vec3;
```

### t_ray
```c
typedef struct s_ray
{
    t_vec3  origin;
    t_vec3  direction;
}   t_ray;
```

### t_camera
```c
typedef struct s_camera
{
    t_vec3  position;
    t_vec3  orientation;
    int     fov;
}   t_camera;
```

### t_light
```c
typedef struct s_light
{
    t_vec3          position;
    double          ratio;
    t_vec3          color;
    struct s_light  *next;
}   t_light;
```

### t_sphere
```c
typedef struct s_sphere
{
    t_vec3  center;
    double  radius;
}   t_sphere;
```

### t_plane
```c
typedef struct s_plane
{
    t_vec3  point;
    t_vec3  normal;
}   t_plane;
```

### t_cylinder
```c
typedef struct s_cylinder
{
    t_vec3  center;
    t_vec3  axis;
    double  diameter;
    double  height;
}   t_cylinder;
```

### t_object
```c
typedef struct s_object
{
    void            *object;
    int             type;
    t_vec3          color;
    struct s_object *next;
}   t_object;
```

### t_scene
```c
typedef struct s_scene
{
    t_camera    camera;
    t_light     *lights;
    t_object    *objects;
    t_light     *ambient_light;
}   t_scene;
```

### t_hit
```c
typedef struct s_hit
{
    double      t;
    t_vec3      point;
    t_vec3      normal;
    t_object    *object;
}   t_hit;
```

---

## Constants

```c
#define WIDTH       800     // Window width
#define HEIGHT      600     // Window height
#define OBJ_SPHERE  1       // Sphere type ID
#define OBJ_PLANE   2       // Plane type ID
#define OBJ_CYLINDER 3      // Cylinder type ID
```

---

## Error Handling

Functions return `NULL` or `-1` on error. Always check return values:

```c
t_scene *scene = parse_scene(filename);
if (!scene)
{
    // Handle error
    return 1;
}
```

---

## Thread Safety

⚠️ miniRT is **not thread-safe**. Do not call API functions from multiple threads.

---

[← Back to Wiki Home](./Home.md)
