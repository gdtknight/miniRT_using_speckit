# Contract: .rt Scene File Format

This document specifies the format for the `.rt` scene description files.

- Each element is identified by a one or two-letter identifier.
- Information for each element is space-separated.
- Colors are represented as three comma-separated integers (R,G,B) in the range [0, 255].
- Vectors (positions, orientations) are represented as three comma-separated floating-point numbers (x,y,z).

## Elements

### Ambient Lighting

- **Identifier**: `A`
- **Format**: `A [ratio] [R,G,B]`
- **Example**: `A 0.2 255,255,255`

### Camera

- **Identifier**: `C`
- **Format**: `C [x,y,z position] [x,y,z orientation vector] [FOV]`
- **Example**: `C -50,0,20 0,0,1 70`

### Light

- **Identifier**: `L`
- **Format**: `L [x,y,z position] [ratio] [R,G,B]`
- **Example**: `L -40,0,30 0.7 255,0,0`

### Sphere

- **Identifier**: `sp`
- **Format**: `sp [x,y,z center] [diameter] [R,G,B]`
- **Example**: `sp 0,0,20 10 255,0,0`

### Plane

- **Identifier**: `pl`
- **Format**: `pl [x,y,z point] [x,y,z normal vector] [R,G,B]`
- **Example**: `pl 0,0,0 0,1,0 0,0,255`

### Cylinder

- **Identifier**: `cy`
- **Format**: `cy [x,y,z center] [x,y,z axis vector] [diameter] [height] [R,G,B]`
- **Example**: `cy 50,0,6 0,0,1 14.2 21.42 10,0,255`
