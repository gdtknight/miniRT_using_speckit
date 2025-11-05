# Cross-Platform Support

miniRT supports both macOS and Linux platforms with automatic detection.

## Platform Detection

The Makefile automatically detects your operating system and configures the appropriate MLX library and build flags.

### macOS (Darwin)
- Uses: `lib/minilibx` (OpenGL-based)
- Frameworks: OpenGL, AppKit
- Key code: ESC = 53

### Linux (Ubuntu/Debian)
- Uses: `lib/minilibx-linux` (X11-based)
- Libraries: X11, Xext
- Key code: ESC = 65307

## Installation

### macOS Setup

```bash
# Prerequisites are already included with Xcode
xcode-select --install

# Build
make
```

### Linux Setup

```bash
# Run automated setup
./setup_linux.sh

# Or manual setup:
# 1. Install dependencies
sudo apt-get update
sudo apt-get install -y gcc make xorg libxext-dev libbsd-dev

# 2. Clone minilibx-linux
mkdir -p lib
cd lib
git clone https://github.com/42Paris/minilibx-linux.git
cd minilibx-linux
make
cd ../..

# 3. Build miniRT
make
```

## Key Differences

### Display System
| Feature | macOS | Linux |
|---------|-------|-------|
| Graphics API | OpenGL | X11 |
| MLX Library | minilibx | minilibx-linux |
| Frameworks | AppKit, OpenGL | X11, Xext |

### Key Codes
| Key | macOS | Linux |
|-----|-------|-------|
| ESC | 53 | 65307 |
| W | 13 | 119 |
| A | 0 | 97 |
| S | 1 | 115 |
| D | 2 | 100 |

### Event Codes
| Event | macOS | Linux |
|-------|-------|-------|
| Window Close | 17 | 17 |
| Expose | 12 | 12 |

## Building

### Check Platform
```bash
make info
```

Output example (macOS):
```
Operating System: Darwin
MLX Directory: lib/minilibx
Compiler Flags: -Wall -Wextra -Werror -I include -I lib/minilibx
Linker Flags: -L lib/minilibx -lmlx -framework OpenGL -framework AppKit
```

Output example (Linux):
```
Operating System: Linux
MLX Directory: lib/minilibx-linux
Compiler Flags: -Wall -Wextra -Werror -I include -I lib/minilibx-linux
Linker Flags: -L lib/minilibx-linux -lmlx -lXext -lX11 -lm
```

### Build Commands
```bash
# Clean and rebuild
make re

# Clean only
make clean

# Full clean (removes executable)
make fclean

# Build and run
make && ./miniRT scenes/bright_test.rt
```

## Troubleshooting

### macOS Issues

**Problem**: "mlx.h not found"
```bash
# Check if minilibx exists
ls lib/minilibx/

# If missing, it should be included in the repo
# If not, you can get it from: https://github.com/42Paris/minilibx
```

**Problem**: "framework not found OpenGL"
```bash
# Install Xcode Command Line Tools
xcode-select --install
```

### Linux Issues

**Problem**: "mlx.h not found"
```bash
# Run setup script
./setup_linux.sh

# Or manually clone minilibx-linux
cd lib
git clone https://github.com/42Paris/minilibx-linux.git
cd minilibx-linux
make
```

**Problem**: "X11 not found"
```bash
# Install X11 development libraries
sudo apt-get install -y xorg libxext-dev
```

**Problem**: Display issues (no window appears)
```bash
# Make sure X server is running
echo $DISPLAY  # Should output something like :0 or :1

# If empty, start X server or use SSH with X forwarding
ssh -X user@host
```

## Testing Cross-Platform

### Test on macOS
```bash
uname -s  # Should output: Darwin
make info
make re
./miniRT scenes/bright_test.rt
```

### Test on Linux
```bash
uname -s  # Should output: Linux
./setup_linux.sh
make info
make re
./miniRT scenes/bright_test.rt
```

## Code Structure

### Platform-Specific Code

**include/minirt.h**:
```c
#ifdef __APPLE__
  #define KEY_ESC 53
  // macOS key codes
#elif __linux__
  #define KEY_ESC 65307
  // Linux key codes
#endif
```

**Makefile**:
```makefile
UNAME := $(shell uname -s)

ifeq ($(UNAME), Darwin)
    # macOS settings
    MLX_DIR = lib/minilibx
    MLX_FLAGS = -framework OpenGL -framework AppKit
else
    # Linux settings
    MLX_DIR = lib/minilibx-linux
    MLX_FLAGS = -lXext -lX11 -lm
endif
```

## Notes

- All rendering logic is platform-independent
- Only MLX initialization and key handling differ between platforms
- BMP export works identically on both platforms
- Scene file format is identical across platforms
- Performance may vary depending on hardware and graphics drivers

## Supported Platforms

✅ macOS (tested on macOS 10.15+)
✅ Ubuntu Linux (tested on 20.04, 22.04)
✅ Debian Linux (tested on 11, 12)
⚠️ Other Linux distributions (should work with X11)
❌ Windows (not supported - use WSL2 with X server)

## Future Support

- [ ] Windows native support
- [ ] Wayland support for Linux
- [ ] ARM architecture optimization
- [ ] Docker containerization for easy setup
