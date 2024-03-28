# Basic C++ SDL2 project

This is an emulator for the [spork_console][] project, which normally runs on custom hardware, for it to run on computers. The purpose is mainly for easier development.

The project is based on this [basic C++ SDL project](https://github.com/aminosbh/basic-cpp-sdl-project).

## Dependencies

- [Git][]
- C/C++ Compiler (gcc, clang, etc.)
- [CMake][]
- [SDL2][SDL] library

**On Debian/Ubuntu based distributions, use the following command:**

```sh
sudo apt install git build-essential pkg-config cmake cmake-data libsdl2-dev
```

## Build instructions

```sh
# Clone this repo
git clone https://github.com/benanderman/spork_console_emulator.git
cd spork_console_emulator

# Clone spork_console repo into src (symlinking can also work if your compiler supports it)
cd src
git clone https://github.com/benanderman/spork_console.git
cd ..

# Create a build folder
mkdir build
cd build

# Build
cmake ..
make

# Run
./spork-console-emulator

# Controls are: arrows, A, S, tab, enter.
```

## Code overview

`include/arduino.h`: Declares (and in some cases defines) the Arduino functions used by [spork_console][].

`src/arduino.cpp`: Defines the functions declared in `arduino.h`, and handles keyboard input.

`src/main.cpp`: Sets up SDL, creates the window, and calls the [spork_console][] entrypoint, `loop()`.

`src/neopixels.cpp`: An alternate definition for `Neopixels` in `spork_console/neopixels.h`, which renders to the window.

`src/renderer.h`: Exposes the renderer and window defined in `main.cpp` for use in `arduino.cpp` and `neopixels.cpp`.

[SDL]: https://www.libsdl.org
[CMake]: https://cmake.org
[Git]: https://git-scm.com
[spork_console]: https://github.com/benanderman/spork_console/
