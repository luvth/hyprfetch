command -v g++ &>/dev/null || {
  echo "g++ required but not installed."
  exit 1
}

g++ -O2 -std=c++17 -Wall -static hyprfetch.cpp -o hyprfetch

[ $? -ne 0 ] && echo "Compilation failed!" && exit 1
