# Tic-Tac-Toe Game

This is a simple Tic-Tac-Toe game implemented in C using the SDL2 library for graphics, SDL2_mixer for sound, and SDL2_image for loading images.

## Prerequisites

To build and run this project, you need to have the following installed:

- [SDL2](https://www.libsdl.org/download-2.0.php)
- [SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/)
- [SDL2_image](https://www.libsdl.org/projects/SDL_image/)
- [SDL2_gfxPrimitives](http://www.ferzkopp.net/wordpress/2016/01/02/sdl_gfx-sdl2_gfx/)

## Building the Project

### Windows (Visual Studio)

1. Open the `Morpion.sln` solution file in Visual Studio.
2. Ensure that the SDL2, SDL2_mixer, SDL2_image, and SDL2_gfxPrimitives libraries are correctly linked in the project settings.
3. Build the project.

### Linux/Mac

1. Install the required libraries:
   ```bash
   sudo apt-get install libsdl2-dev libsdl2-mixer-dev libsdl2-image-dev
