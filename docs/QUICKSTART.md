# miniRT - Quick Start Guide

## 🚀 Quick Installation

### macOS
```bash
git clone <your-repo>
cd miniRT_speckit
make
./miniRT scenes/bright_test.rt
```

### Linux (Ubuntu/Debian)
```bash
git clone <your-repo>
cd miniRT_speckit
./setup_linux.sh
make
./miniRT scenes/bright_test.rt
```

## 🎮 Controls

- **ESC** - Exit program
- **Window Close Button** - Exit program

## 📁 Output

- **Screen Display** - Real-time rendering in MLX window
- **output.bmp** - Saved image file (can be opened with any image viewer)

## 🎨 Creating Scenes

Create a `.rt` file with:

```
A 0.3 255,255,255                    # Ambient light
C 0,0,-20 0,0,1 70                   # Camera
L -10,10,0 0.8 255,255,255           # Light source

sp -5,0,20 10 255,0,0                # Red sphere
sp 5,0,20 10 0,255,0                 # Green sphere
sp 0,8,25 8 0,0,255                  # Blue sphere
pl 0,-10,0 0,1,0 200,200,200         # Gray plane
```

Run: `./miniRT your_scene.rt`

## 🔧 Troubleshooting

### "Error\n" message
- Scene file not found or invalid format
- Check file path and syntax

### Black screen in window
- Check `output.bmp` file - rendering may still work
- May be MLX display issue (file rendering is still correct)

### Build errors on Linux
- Run `./setup_linux.sh` first
- Install dependencies: `sudo apt-get install gcc make xorg libxext-dev libbsd-dev`

## 📚 More Information

- Full documentation: [README.md](../README.md)
- Platform details: [CROSS_PLATFORM.md](CROSS_PLATFORM.md)
- Scene format: See example files in `scenes/` directory

## ✨ Features

✅ Spheres, planes, cylinders
✅ Multiple light sources
✅ Phong lighting model
✅ Shadows
✅ BMP file export
✅ Cross-platform (macOS & Linux)
✅ Real-time display
