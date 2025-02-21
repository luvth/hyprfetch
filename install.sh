#!/bin/bash

[ "$EUID" -ne 0 ] && echo "Please run as root (with sudo)" && exit 1

command -v g++ &> /dev/null || { echo "g++ required but not installed."; exit 1; }

g++ -O2 -std=c++17 -Wall -static hyprfetch.cpp -o hyprfetch

[ $? -ne 0 ] && echo "Compilation failed!" && exit 1

cp hyprfetch /usr/bin/
chmod 755 /usr/bin/hyprfetch
rm hyprfetch
rm -rf ../hyprfetch
echo "Installation complete! You can now run 'hyprfetch' from anywhere."
