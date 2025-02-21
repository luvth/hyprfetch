#!/bin/bash

[ "$EUID" -ne 0 ] && echo "Please run as root (with sudo)" && exit 1

chmod +x ./compile.sh
./compile.sh

cp hyprfetch /usr/bin/
chmod 755 /usr/bin/hyprfetch
rm hyprfetch
rm -rf ../hyprfetch
echo "Installation complete! You can now run 'hyprfetch' from anywhere."
