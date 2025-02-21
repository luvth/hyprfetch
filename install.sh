#!/bin/bash

# Check if running as root
if [ "$EUID" -ne 0 ]; then 
    echo "Please run as root (with sudo)"
    exit 1
fi

# Check for required build tools
if ! command -v g++ &> /dev/null; then
    echo "g++ is required but not installed."
    echo "Please install build-essential or g++"
    exit 1
fi

echo "Compiling hyprfetch..."
g++ -O2 -std=c++17 -Wall -static hyprfetch.cpp -o hyprfetch

if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

echo "Installing to /usr/bin..."
cp hyprfetch /usr/bin/
chmod 755 /usr/bin/hyprfetch

echo "Cleaning up..."
rm hyprfetch

echo "Installation complete! You can now run 'hyprfetch' from anywhere."
