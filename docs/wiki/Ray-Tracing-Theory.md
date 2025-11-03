# Ray Tracing Theory

Understanding the mathematics and algorithms behind miniRT.

---

## What is Ray Tracing?

Ray tracing is a rendering technique that simulates the physical behavior of light. Instead of projecting geometry onto the screen (rasterization), ray tracing follows light paths:

1. **Cast rays** from camera through each pixel
2. **Find intersections** with scene geometry
3. **Calculate lighting** at hit points
4. **Determine color** based on material and lights

---

## Ray Representation

A ray is defined by:
- **Origin** (O): Starting point
- **Direction** (D): Unit vector indicating direction

```c
typedef struct s_ray
{
    t_vec3  origin;     // Starting point
    t_vec3  direction;  // Direction (normalized)
}   t_ray;
```

Any point P along the ray:
```
P(t) = O + t * D
```

where `t` is the distance parameter (t ≥ 0)

---

## Camera and Ray Generation

### Camera Setup

```c
typedef struct s_camera
{
    t_vec3  position;      // Camera location
    t_vec3  orientation;   // Look direction
    int     fov;           // Field of view (degrees)
}   t_camera;
```

### Generating Rays

For each pixel (i, j):

```c
// 1. Calculate viewport coordinates
fov_rad = fov * π / 180
aspect_ratio = width / height
x_cam = (2 * (i + 0.5) / width - 1) * tan(fov_rad/2) * aspect_ratio
y_cam = (1 - 2 * (j + 0.5) / height) * tan(fov_rad/2)

// 2. Create ray direction
direction = normalize(x_cam, y_cam, 1)

// 3. Ray from camera
ray = { position, direction }
```

---

## Intersection Tests

### Sphere Intersection

Given:
- Sphere center: C
- Sphere radius: r
- Ray: O + tD

Solve for t:
```
||O + tD - C||² = r²

Expanding:
t² * ||D||² + 2t * dot(D, O-C) + ||O-C||² - r² = 0
```

Quadratic form: `at² + 2bt + c = 0`

where:
```c
oc = ray.origin - sphere.center;
a = dot(ray.direction, ray.direction);  // = 1 if normalized
b = dot(ray.direction, oc);
c = dot(oc, oc) - radius * radius;
```

Discriminant:
```c
discriminant = b² - ac
```

Solutions:
- `discriminant < 0`: No intersection
- `discriminant = 0`: One intersection (tangent)
- `discriminant > 0`: Two intersections

```c
t1 = (-b - sqrt(discriminant)) / a;  // Near hit
t2 = (-b + sqrt(discriminant)) / a;  // Far hit
```

Return smallest positive t.

### Plane Intersection

Given:
- Plane point: P
- Plane normal: N
- Ray: O + tD

Solve for t:
```
dot(P - (O + tD), N) = 0
dot(P - O, N) = t * dot(D, N)
```

Solution:
```c
denom = dot(ray.direction, plane.normal);

if (fabs(denom) > epsilon)  // Not parallel
{
    t = dot(plane.point - ray.origin, plane.normal) / denom;
    if (t > epsilon)  // Forward intersection
        return t;
}
return -1;  // No intersection
```

### Cylinder Intersection

More complex - intersection with:
1. **Infinite cylinder body**
2. **Two cap planes**

For body intersection, project to 2D and solve quadratic equation.

---

## Surface Normals

Normal vectors point perpendicular to surfaces.

### Sphere Normal
```c
normal = normalize(hit_point - sphere.center);
```

### Plane Normal
```c
normal = plane.normal;  // Already defined
```

### Cylinder Normal

Body:
```c
// Project hit point to axis
projection = center + dot(hit_point - center, axis) * axis;
normal = normalize(hit_point - projection);
```

Caps:
```c
normal = cylinder.axis;  // or -axis for bottom cap
```

---

## Finding Closest Intersection

Algorithm:
```c
closest_t = infinity;
closest_object = NULL;

for each object in scene:
    t = intersect(ray, object);
    if (t > 0 && t < closest_t):
        closest_t = t;
        closest_object = object;

if (closest_object):
    hit_point = ray.origin + closest_t * ray.direction;
    calculate_normal(closest_object, hit_point);
    return hit_point;

return background_color;
```

---

## Coordinate Systems

### World Space
- Global 3D coordinates
- Objects defined in world space

### Camera Space
- Relative to camera
- Z-axis points forward
- Y-axis points up
- X-axis points right

### Screen Space
- 2D pixel coordinates
- Origin at top-left (0, 0)
- Bottom-right at (width-1, height-1)

---

## Optimization Techniques

### Early Ray Termination
Stop tracing when ray clearly misses all objects.

### Bounding Volumes
Test intersection with simple shapes first:
- Axis-Aligned Bounding Boxes (AABB)
- Bounding spheres

### Spatial Partitioning
Organize objects in space:
- Octrees
- k-d trees
- Bounding Volume Hierarchies (BVH)

*Note: miniRT uses brute-force intersection testing for simplicity.*

---

## Limitations

### No Secondary Rays
- No reflections
- No refractions
- No recursive tracing

### Single Sample per Pixel
- No anti-aliasing
- Jagged edges
- Aliasing artifacts

### No Acceleration Structure
- Tests all objects for every ray
- O(n) complexity per ray

---

## Mathematical Notation

| Symbol | Meaning |
|--------|---------|
| O | Ray origin |
| D | Ray direction |
| t | Distance parameter |
| N | Surface normal |
| L | Light direction |
| V | View direction |
| R | Reflection vector |

---

## Code Example

Complete ray-object intersection:

```c
t_hit find_closest_intersection(t_scene *scene, t_ray ray)
{
    t_hit       hit;
    t_object    *obj;
    double      t;
    double      closest_t;

    closest_t = INFINITY;
    hit.object = NULL;
    obj = scene->objects;
    
    while (obj)
    {
        if (obj->type == OBJ_SPHERE)
            t = intersect_sphere(ray, obj->object);
        else if (obj->type == OBJ_PLANE)
            t = intersect_plane(ray, obj->object);
        else if (obj->type == OBJ_CYLINDER)
            t = intersect_cylinder(ray, obj->object);
        
        if (t > 0 && t < closest_t)
        {
            closest_t = t;
            hit.t = t;
            hit.object = obj;
        }
        obj = obj->next;
    }
    
    return hit;
}
```

---

## Further Reading

- [Lighting Model](./Lighting-Model.md)
- [Vector Mathematics](./Vector-Mathematics.md)
- [Performance Optimization](./Performance.md)

---

[← Back to Wiki Home](./Home.md)
