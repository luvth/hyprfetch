# Hyprfetch

![Hyprfetch example](https://i.imgur.com/KmUAMg8.png)

Hyprfetch is a lightweight and customizable system information fetch tool, similar to Neofetch, designed for minimalism and efficiency. It displays essential system details in a visually appealing way, with color-coded information and a dynamic progress bar for system resource usage.

## Features

- **User and Host Display**: Shows the logged-in user's name and the hostname.
- **Uptime Tracking**: Displays system uptime in a human-readable format.
- **Operating System Information**:
  - Distro Name
  - Kernel Version
  - Package Count (Pacman-based systems)
- **System Resources Monitoring**:
  - CPU Usage (with a progress bar)
  - RAM Usage (with a progress bar)
  - Disk Usage (with a progress bar)
- **Window Manager Detection**: Identifies the currently running WM.
- **Terminal Detection**: Displays the active terminal emulator.
- **Shell Detection**: Shows the shell in use.
- **Dynamic Color Scheme**: Utilizes ANSI escape codes to enhance readability.
- **Minimal Dependencies**: Relies only on standard Linux utilities.

## Installation

To compile Hyprfetch, ensure you have a C++ compiler installed (e.g., `g++`) and run:

```sh
git clone https://github.com/luvth/hyprfetch
cd hyprfetch
chmod +x install.sh
```

Then, run the executable:

```sh
sudo ./install.sh
```

## Usage

Simply execute Hyprfetch in the terminal:

```sh
hyprfetch
```

## Customization

You can modify the C++ source code to:
- Change colors
- Modify displayed information
- Adjust progress bar size

## Contributions

Feel free to fork the repository and submit pull requests for improvements!