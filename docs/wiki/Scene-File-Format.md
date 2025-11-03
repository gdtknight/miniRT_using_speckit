# Scene File Format

Complete reference for `.rt` scene file format.

---

## Overview

Scene files use a simple line-based format where each line defines either:
- Ambient lighting (`A`)
- Camera (`C`)
- Light source (`L`)
- Geometric object (`sp`, `pl`, `cy`)

---

## Syntax Rules

- One element per line
- Elements can appear in any order
- Comments start with `#`
- Whitespace is ignored
- Values are separated by commas
- Color values: 0-255 (RGB)

---

## Elements

### Ambient Lighting
```
A <ratio> <R,G,B>
```

**Parameters:**
- `ratio`: Ambient light ratio (0.0 - 1.0)
- `R,G,B`: Color values (0-255)

**Example:**
```
A 0.2 255,255,255
```

**Notes:**
- Only one ambient light allowed
- Affects all objects globally

---

### Camera
```
C <x,y,z> <nx,ny,nz> <fov>
```

**Parameters:**
- `x,y,z`: Camera position
- `nx,ny,nz`: Orientation vector (normalized)
- `fov`: Field of view in degrees (0-180)

**Example:**
```
C 0,0,-20 0,0,1 70
```

**Notes:**
- Only one camera allowed
- Orientation vector will be normalized automatically

---

### Light Source
```
L <x,y,z> <brightness> <R,G,B>
```

**Parameters:**
- `x,y,z`: Light position
- `brightness`: Light intensity (0.0 - 1.0)
- `R,G,B`: Light color (0-255)

**Example:**
```
L -40,0,30 0.7 255,255,255
```

**Notes:**
- Multiple lights supported
- Point light source (omnidirectional)

---

### Sphere
```
sp <x,y,z> <diameter> <R,G,B>
```

**Parameters:**
- `x,y,z`: Center position
- `diameter`: Sphere diameter
- `R,G,B`: Object color (0-255)

**Example:**
```
sp 0,0,20 10 255,0,0
```

---

### Plane
```
pl <x,y,z> <nx,ny,nz> <R,G,B>
```

**Parameters:**
- `x,y,z`: Point on the plane
- `nx,ny,nz`: Normal vector (normalized)
- `R,G,B`: Object color (0-255)

**Example:**
```
pl 0,-5,0 0,1,0 100,100,100
```

**Notes:**
- Infinite plane
- Normal vector defines orientation

---

### Cylinder
```
cy <x,y,z> <nx,ny,nz> <diameter> <height> <R,G,B>
```

**Parameters:**
- `x,y,z`: Center position
- `nx,ny,nz`: Axis direction (normalized)
- `diameter`: Cylinder diameter
- `height`: Cylinder height
- `R,G,B`: Object color (0-255)

**Example:**
```
cy 5,0,10 0,1,0 3.0 10.0 0,255,0
```

**Notes:**
- Finite cylinder with caps
- Axis vector defines orientation

---

## Complete Example

```
# Ambient lighting
A 0.2 255,255,255

# Camera
C 0,0,-20 0,0,1 70

# Main light
L -40,0,30 0.7 255,255,255

# Red sphere
sp 0,0,20 10 255,0,0

# Ground plane
pl 0,-5,0 0,1,0 100,100,100

# Green cylinder
cy 5,0,10 0,1,0 3.0 10.0 0,255,0

# Blue sphere
sp -5,0,15 5 0,0,255
```

---

## Best Practices

### Color Selection
- Use complementary colors for better contrast
- Avoid pure white (255,255,255) for objects - use slight tints
- Ground planes work well with neutral colors (100,100,100)

### Lighting
- Start with one main light source
- Add fill lights with lower brightness
- Ambient ratio of 0.1-0.3 usually works well

### Camera Positioning
- Position camera behind objects looking forward
- FOV of 60-80 degrees gives natural perspective
- Experiment with angles for dramatic effects

### Object Placement
- Use Y-axis for vertical positioning
- Z-axis for depth (positive = away from camera)
- Group related objects together

---

## Validation

The parser will validate:
- ✅ Correct number of parameters
- ✅ Value ranges (colors: 0-255, ratios: 0-1)
- ✅ Vector normalization
- ✅ Required elements (A, C, at least one object)

Common errors:
- ❌ Missing required elements
- ❌ Invalid color values (> 255 or < 0)
- ❌ Invalid ratios (> 1.0 or < 0.0)
- ❌ Malformed syntax

---

## Tips & Tricks

### Creating Shadows
Place objects between light source and other objects:
```
L 0,10,0 0.8 255,255,255
sp 0,5,0 2 255,0,0        # Shadow caster
pl 0,0,0 0,1,0 200,200,200  # Shadow receiver
```

### Layering Objects
Create depth by varying Z positions:
```
sp 0,0,10 5 255,0,0    # Front
sp 0,0,15 5 0,255,0    # Middle
sp 0,0,20 5 0,0,255    # Back
```

### Scene Composition
Follow the rule of thirds for pleasing composition:
```
sp -3,2,15 5 255,0,0   # Off-center
sp 3,-2,20 5 0,0,255   # Balance
```

---

[← Back to Wiki Home](./Home.md)
