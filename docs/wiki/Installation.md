# Installation Guide

Complete guide to installing and building miniRT.

---

## Prerequisites

### System Requirements

- **Operating System**: macOS
- **Xcode**: Command Line Tools
- **Memory**: 512 MB RAM minimum
- **Disk Space**: 100 MB free space

### Software Dependencies

```bash
# Check if Xcode Command Line Tools are installed
xcode-select -p

# If not installed, install them
xcode-select --install
```

---

## Installation Methods

### Method 1: Clone and Build (Recommended)

```bash
# 1. Clone the repository
git clone https://github.com/gdtknight/miniRT_using_speckit.git

# 2. Navigate to project directory
cd miniRT_using_speckit

# 3. Build the project
make

# 4. Test the installation
./miniRT scenes/simple.rt
```

### Method 2: Download Release

```bash
# Download latest release
curl -LO https://github.com/gdtknight/miniRT_using_speckit/archive/refs/heads/main.zip

# Extract
unzip main.zip
cd miniRT_using_speckit-main

# Build
make
```

---

## Build Options

### Standard Build
```bash
make
```

### Clean Build
```bash
make fclean && make
```

### Build with Tests
```bash
make test
```

### Debug Build
```bash
make CFLAGS="-Wall -Wextra -Werror -g -I include -I lib/minilibx"
```

---

## Verification

### Test Installation

```bash
# Run with test scene
./miniRT scenes/simple.rt
```

Expected output:
```
Parsing scene: scenes/simple.rt
Initializing MLX...
Rendering scene...
Saving to output.bmp...
Done! Displaying (ESC to exit).
```

### Check Norminette Compliance

```bash
# Install norminette (if not already installed)
pip3 install norminette

# Check compliance
norminette src/ include/
```

Expected output: `OK!` for all files

---

## Troubleshooting

### Common Issues

#### 1. MiniLibX Not Found

**Error:**
```
fatal error: 'mlx.h' file not found
```

**Solution:**
```bash
# Check if MiniLibX is in lib/minilibx
ls lib/minilibx

# If missing, the library should be included in the repo
# Try re-cloning
```

#### 2. Compilation Errors

**Error:**
```
undefined reference to...
```

**Solution:**
```bash
# Clean and rebuild
make fclean
make
```

#### 3. Permission Denied

**Error:**
```
./miniRT: Permission denied
```

**Solution:**
```bash
chmod +x miniRT
```

#### 4. Scene File Not Found

**Error:**
```
Error
Failed to parse scene file
```

**Solution:**
```bash
# Check file exists
ls scenes/simple.rt

# Use absolute path
./miniRT $(pwd)/scenes/simple.rt
```

---

## Uninstallation

```bash
# Remove compiled files
make fclean

# Remove project directory
cd ..
rm -rf miniRT_using_speckit
```

---

## Platform-Specific Notes

### macOS Intel
- Standard installation works
- MiniLibX uses X11

### macOS Apple Silicon (M1/M2)
- May need Rosetta 2 for MiniLibX
- Install Rosetta if needed:
  ```bash
  softwareupdate --install-rosetta
  ```

### Linux (Not officially supported)
- Requires X11 development libraries
- May need different MiniLibX version

---

## Next Steps

1. ✅ Installation complete
2. 📖 Read [Quick Start Guide](./Quick-Start.md)
3. 🎨 Create your first scene
4. 📚 Explore [Scene File Format](./Scene-File-Format.md)

---

[← Back to Wiki Home](./Home.md) | [Next: Quick Start →](./Quick-Start.md)
