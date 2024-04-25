## Game Of Life

![# Game Of Life](./game-of-life-loop-cropped.gif)

# For MacOS
    1- First, you must download and install **XQuartz**, from the official website: https://www.xquartz.org/
    You can use brew :
        > brew install --cask xquartz
    2- run make
        > make
# For Linux
    For Linux you can run 'make' directly, but ensure you have X11 installed.
    > make

# get started:

Run the following commands in linux env:

`$ make`
`$ ./gol 10 100`

You can tweak the parameters given like so:
`$ ./gol [cell size] [cell count]`
(keep in mind there is a cap of 1000px that you can modify
by changing the `WIN_CAP` definition in the `gol.h` header).
