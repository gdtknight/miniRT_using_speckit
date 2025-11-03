# Quick Start Guide

Get started with miniRT in 5 minutes!

---

## Step 1: Installation

```bash
# Clone the repository
git clone https://github.com/gdtknight/miniRT_using_speckit.git
cd miniRT_using_speckit

# Build the project
make
```

Expected output:
```
gcc -Wall -Wextra -Werror ...
Compilation complete!
```

---

## Step 2: Run Your First Scene

```bash
./miniRT scenes/simple.rt
```

You should see:
1. Console output showing progress
2. A window opens with rendered scene
3. `output.bmp` file created

**Controls:**
- Press **ESC** to exit

---

## Step 3: Understand the Scene File

Open `scenes/simple.rt`:

```
# Ambient light (ratio 0.2, white)
A 0.2 255,255,255

# Camera (position, direction, FOV)
C 0,0,-20 0,0,1 70

# Light source (position, brightness 0.7, white)
L -40,0,30 0.7 255,255,255

# Red sphere (center, diameter 10, red color)
sp 0,0,20 10 255,0,0

# Ground plane (point, normal up, gray)
pl 0,-5,0 0,1,0 100,100,100
```

---

## Step 4: Create Your Own Scene

Create `my_first_scene.rt`:

```bash
cat > my_first_scene.rt << EOF
# Ambient lighting
A 0.2 255,255,255

# Camera looking forward
C 0,0,-20 0,0,1 70

# Main light from above-left
L -10,10,0 0.8 255,255,255

# Blue sphere in center
sp 0,0,15 8 0,100,255

# Green sphere to the left
sp -8,0,18 5 100,255,100

# Red sphere to the right
sp 8,2,18 4 255,100,100

# Ground plane
pl 0,-5,0 0,1,0 150,150,150
EOF
```

Render it:
```bash
./miniRT my_first_scene.rt
```

---

## Step 5: Experiment!

### Try Different Colors

```
# Bright red
sp 0,0,15 5 255,0,0

# Sky blue
sp 0,0,15 5 135,206,235

# Gold
sp 0,0,15 5 255,215,0
```

### Move Objects

```
# Far away (Z = 30)
sp 0,0,30 5 255,0,0

# Close up (Z = 10)
sp 0,0,10 5 255,0,0

# Above camera (Y = 5)
sp 0,5,15 5 255,0,0
```

### Adjust Lighting

```
# Bright light
L -10,10,0 1.0 255,255,255

# Dim light
L -10,10,0 0.3 255,255,255

# Colored light (red tint)
L -10,10,0 0.7 255,100,100
```

### Change Camera

```
# Wide angle (FOV 90)
C 0,0,-20 0,0,1 90

# Narrow angle (FOV 40)
C 0,0,-20 0,0,1 40

# From side
C -20,0,0 1,0,0 70

# From above
C 0,20,0 0,-1,0 70
```

---

## Common Patterns

### Three Sphere Composition

```
A 0.2 255,255,255
C 0,0,-20 0,0,1 70
L -10,15,-5 0.7 255,255,255

# Large back sphere
sp 0,0,25 12 100,100,255

# Medium middle sphere
sp -5,-2,18 6 255,100,100

# Small front sphere
sp 3,-3,12 4 100,255,100

pl 0,-5,0 0,1,0 150,150,150
```

### Sunset Scene

```
A 0.1 255,200,150
C 0,2,-15 0,-0.1,1 70
L -20,10,0 0.8 255,150,100

sp 0,-1000,0 1990 200,150,100  # Large sphere as "sun"
pl 0,0,0 0,1,0 100,80,60        # Ground
```

### Multiple Lights

```
A 0.1 255,255,255
C 0,0,-20 0,0,1 70

# Main light
L -10,10,-5 0.6 255,255,255

# Fill light
L 10,5,-5 0.3 150,150,200

# Back light
L 0,5,30 0.4 255,200,150

sp 0,0,15 8 255,100,100
pl 0,-5,0 0,1,0 150,150,150
```

---

## Tips for Beginners

### 1. Start Simple
Begin with one object and one light. Add complexity gradually.

### 2. Use Consistent Units
- Position in world units
- Diameter (not radius!)
- Stay consistent with your scale

### 3. Camera Placement
- Position camera behind scene (negative Z)
- Point forward (0,0,1 direction)
- FOV 60-80 for natural perspective

### 4. Lighting
- Ambient: 0.1-0.3 for most scenes
- Main light: 0.6-0.8 brightness
- Position lights above and to side for depth

### 5. Colors
- Avoid pure white objects (255,255,255)
- Use slight tints for more interest
- Ground planes: neutral grays work well

---

## Troubleshooting

### Scene Won't Render

**Check:**
- File exists and path is correct
- File has .rt extension
- File includes A, C, and at least one object
- All color values are 0-255
- All ratios are 0.0-1.0

### Objects Not Visible

**Check:**
- Object Z position is positive (in front of camera)
- Object is within camera view
- Object has non-zero size
- Colors are not too dark

### Lighting Too Dark/Bright

**Adjust:**
- Ambient ratio (A line)
- Light brightness (L line)
- Light position (closer = brighter)

---

## Next Steps

1. ✅ Created your first scene
2. 📖 Read [Scene File Format](./Scene-File-Format.md) for details
3. 🎨 Try example scenes in `scenes/` directory
4. 📚 Learn [Ray Tracing Theory](./Ray-Tracing-Theory.md)
5. 🔧 Explore [API Reference](./API-Reference.md)

---

## Example Gallery

Browse complete examples in the repository:

- `scenes/simple.rt` - Single sphere, basic lighting
- `scenes/spheres.rt` - Multiple spheres, color variety
- `scenes/test.rt` - All object types, complex scene

---

## Challenge Yourself

Try creating:
- ☐ A scene with 5+ objects
- ☐ A scene using only cylinders
- ☐ A scene with 3+ light sources
- ☐ A sunset/sunrise scene
- ☐ An abstract composition

Share your creations!

---

[← Back to Wiki Home](./Home.md) | [Next: Scene Format →](./Scene-File-Format.md)
