## Game Of Life

![# Game Of Life](./game-of-life-loop-cropped.gif)
# Installation
## macOS
You'll need **XQuartz** to run the program. Install it from the official website: https://www.xquartz.org/ or using Homebrew:
You can use brew :

> `brew install --cask xquartz`

Reboot the system 

>`reboot`

## Linux
Most Linux distributions have X11 libraries pre-installed.
If not, use your distribution's package manager for installation:
example for Debian/Ubuntu

>`sudo apt-get install gcc make xorg libxext-dev libbsd-dev`

# get started:

Build the game
>`make`

Run the game
>`./gol [cell size] [cell count]`

example

>`./gol 10 100`

PS: there is a cap of 1000px that you can modify
by changing the `WIN_CAP` definition in the `gol.h` header.
