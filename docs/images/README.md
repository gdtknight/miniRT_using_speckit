# Images

This directory contains images used in the documentation.

## Screenshots

Place rendered scene images here for use in README and Wiki:

- `banner.png` - Main banner image (1200x400)
- `logo.png` - Project logo (200x200)
- Example renders from scenes

## Creating Screenshots

```bash
# Render a scene
./miniRT scenes/simple.rt

# output.bmp is created automatically
# Convert BMP to PNG if needed
```

## Image Guidelines

- Use PNG format for documentation
- Keep file sizes reasonable (<500KB)
- Use descriptive filenames
- Include alt text in markdown

## Current Images

The following rendered images are available in the project root:
- `render_fixed.png` - Simple scene render
- `render_spheres.png` - Multiple spheres
- `render_v2.png` - Complex scene

Copy these to `docs/images/` for documentation use.
