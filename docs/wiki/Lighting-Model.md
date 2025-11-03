# Lighting Model

Understanding the Phong illumination model used in miniRT.

---

## Overview

miniRT implements the **Phong Reflection Model**, a simple but effective lighting model that simulates three types of light reflection:

1. **Ambient** - Background illumination
2. **Diffuse** - Matte surface reflection
3. **Specular** - Shiny highlights

---

## Phong Equation

The final color at a point is:

```
I = Ia + Id + Is

where:
  Ia = ambient component
  Id = diffuse component
  Is = specular component
```

---

## Ambient Lighting

Global constant illumination that affects all surfaces equally.

```
Ia = ka * Iamb * Ocolor

where:
  ka = ambient coefficient (scene ambient ratio)
  Iamb = ambient light color
  Ocolor = object color
```

**Purpose:**
- Simulates indirect lighting
- Prevents completely black shadows
- Provides base illumination

**Implementation:**
```c
t_vec3 ambient;

ambient.x = scene->ambient_light->ratio * 
            scene->ambient_light->color.x * 
            object->color.x / 255.0;
ambient.y = ...
ambient.z = ...
```

---

## Diffuse Lighting

Simulates rough, matte surfaces using Lambert's cosine law.

```
Id = kd * Ilight * max(0, N · L)

where:
  kd = diffuse coefficient (usually 1.0)
  Ilight = light source color * intensity
  N = surface normal (normalized)
  L = direction to light (normalized)
  N · L = cosine of angle between normal and light
```

**Key Properties:**
- View-independent (looks same from all angles)
- Maximum when light perpendicular to surface (N · L = 1)
- Zero when light parallel or behind surface (N · L ≤ 0)

**Implementation:**
```c
t_vec3  light_dir;
double  diffuse_intensity;

light_dir = vec3_normalize(vec3_sub(light->position, hit.point));
diffuse_intensity = fmax(0.0, vec3_dot(hit.normal, light_dir));

diffuse.x = diffuse_intensity * light->color.x * object->color.x / 255.0;
diffuse.y = ...
diffuse.z = ...
```

---

## Specular Lighting

Simulates shiny surfaces with highlights.

```
Is = ks * Ilight * max(0, R · V)^n

where:
  ks = specular coefficient (usually 1.0)
  Ilight = light source color * intensity
  R = reflected light direction
  V = view direction (toward camera)
  n = shininess exponent (higher = smaller highlight)
```

**Reflection Vector:**
```
R = 2(N · L)N - L
```

**Key Properties:**
- View-dependent (changes with camera angle)
- Creates bright highlights on shiny surfaces
- Controlled by shininess parameter

**Implementation:**
```c
t_vec3  reflect_dir;
t_vec3  view_dir;
double  spec_intensity;

// R = 2(N·L)N - L
reflect_dir = vec3_sub(
    vec3_mul(hit.normal, 2.0 * vec3_dot(hit.normal, light_dir)),
    light_dir
);

// V = direction to camera
view_dir = vec3_normalize(vec3_sub(camera.position, hit.point));

// Specular intensity
spec_intensity = pow(fmax(0.0, vec3_dot(reflect_dir, view_dir)), shininess);

specular.x = spec_intensity * light->color.x;
specular.y = ...
specular.z = ...
```

*Note: miniRT uses simplified specular without material properties.*

---

## Multiple Light Sources

Sum contributions from all lights:

```c
t_vec3  total_color;
t_light *light;

// Start with ambient
total_color = calculate_ambient(scene, object);

// Add each light's contribution
light = scene->lights;
while (light)
{
    diffuse = calculate_diffuse(light, hit);
    specular = calculate_specular(light, hit, camera);
    
    total_color = vec3_add(total_color, diffuse);
    total_color = vec3_add(total_color, specular);
    
    light = light->next;
}
```

---

## Shadow Calculation

Optional enhancement to check if light is blocked:

```c
bool in_shadow(t_scene *scene, t_vec3 point, t_vec3 light_pos)
{
    t_ray   shadow_ray;
    t_vec3  light_dir;
    double  light_dist;
    t_hit   shadow_hit;
    
    // Ray from surface to light
    light_dir = vec3_sub(light_pos, point);
    light_dist = vec3_length(light_dir);
    shadow_ray.origin = point;
    shadow_ray.direction = vec3_normalize(light_dir);
    
    // Check if any object blocks the light
    shadow_hit = find_closest_intersection(scene, shadow_ray);
    
    return (shadow_hit.object && shadow_hit.t < light_dist);
}
```

If in shadow, skip diffuse and specular for that light.

*Note: Shadow calculation not included in basic miniRT.*

---

## Color Calculation

### Combining Components

```c
final_color = ambient + sum(diffuse_i + specular_i)
```

### Clamping

Ensure color values stay in valid range:

```c
color.x = fmin(255.0, fmax(0.0, color.x));
color.y = fmin(255.0, fmax(0.0, color.y));
color.z = fmin(255.0, fmax(0.0, color.z));
```

### Gamma Correction

*Optional enhancement:*

```c
color.x = pow(color.x / 255.0, 1.0 / 2.2) * 255.0;
color.y = ...
color.z = ...
```

---

## Visual Examples

### Ambient Only
- Flat, even lighting
- No depth perception
- All surfaces visible but dull

### Diffuse Only
- Matte appearance
- Good depth perception
- No highlights

### Diffuse + Specular
- Realistic appearance
- Highlights on spheres
- Material differentiation

### All Components
- Best overall result
- Ambient prevents pure black
- Diffuse provides form
- Specular adds realism

---

## Parameter Tuning

### Ambient Ratio (0.0 - 1.0)
- **Low (0.1 - 0.2)**: Dramatic shadows, high contrast
- **Medium (0.3 - 0.5)**: Balanced lighting
- **High (0.6 - 1.0)**: Flat, washed out

**Recommended:** 0.2

### Light Brightness (0.0 - 1.0)
- **Low (0.3 - 0.5)**: Subtle lighting
- **Medium (0.6 - 0.8)**: Standard lighting
- **High (0.9 - 1.0)**: Very bright, may clip

**Recommended:** 0.7

### Shininess (1 - 200)
- **Low (1 - 10)**: Large, soft highlights (plastic)
- **Medium (20 - 50)**: Medium highlights (painted surface)
- **High (100 - 200)**: Small, sharp highlights (metal)

**Default in miniRT:** Not configurable per object

---

## Limitations

### No Material Properties
- All objects have same reflection properties
- Cannot distinguish between materials
- No control over shininess per object

### No Shadows
- Basic implementation skips shadow testing
- Light passes through all objects
- Reduces realism

### No Indirect Lighting
- Only direct light considered
- No light bouncing
- No color bleeding

---

## Code Example

Complete lighting calculation:

```c
t_vec3  calculate_lighting(t_scene *scene, t_hit hit)
{
    t_vec3  color;
    t_vec3  diffuse;
    t_light *light;
    t_vec3  light_dir;
    double  diff_intensity;
    
    // Ambient component
    color.x = scene->ambient_light->ratio * 
              scene->ambient_light->color.x * 
              hit.object->color.x / 255.0;
    color.y = ...
    color.z = ...
    
    // Add contribution from each light
    light = scene->lights;
    while (light)
    {
        // Direction to light
        light_dir = vec3_normalize(
            vec3_sub(light->position, hit.point)
        );
        
        // Diffuse intensity (Lambert)
        diff_intensity = fmax(0.0, 
            vec3_dot(hit.normal, light_dir)
        );
        
        // Add diffuse component
        color.x += diff_intensity * light->ratio * 
                   light->color.x * 
                   hit.object->color.x / 255.0;
        color.y += ...
        color.z += ...
        
        light = light->next;
    }
    
    // Clamp to valid range
    color.x = fmin(255.0, fmax(0.0, color.x));
    color.y = fmin(255.0, fmax(0.0, color.y));
    color.z = fmin(255.0, fmax(0.0, color.z));
    
    return color;
}
```

---

## Further Reading

- [Ray Tracing Theory](./Ray-Tracing-Theory.md)
- [Vector Mathematics](./Vector-Mathematics.md)
- [Scene File Format](./Scene-File-Format.md)

---

[← Back to Wiki Home](./Home.md)
