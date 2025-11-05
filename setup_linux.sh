#!/bin/bash
# Setup script for Linux (Ubuntu/Debian)

echo "=== miniRT Linux Setup ==="
echo ""

# Check if running on Linux
if [[ "$(uname -s)" != "Linux" ]]; then
    echo "This script is for Linux only."
    echo "Current OS: $(uname -s)"
    exit 1
fi

# Install required packages
echo "Installing required packages..."
sudo apt-get update
sudo apt-get install -y gcc make xorg libxext-dev libbsd-dev

# Clone and build minilibx-linux
if [ ! -d "lib/minilibx-linux" ]; then
    echo ""
    echo "Cloning minilibx-linux..."
    mkdir -p lib
    cd lib
    git clone https://github.com/42Paris/minilibx-linux.git
    cd minilibx-linux
    echo ""
    echo "Building minilibx-linux..."
    make
    cd ../..
else
    echo ""
    echo "minilibx-linux already exists."
fi

echo ""
echo "=== Setup Complete ==="
echo ""
echo "Now you can build miniRT with: make"
echo "Run with: ./miniRT scenes/bright_test.rt"
