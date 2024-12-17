# Tic-Tac-Toe Game

This is a simple and interactive Tic-Tac-Toe game implemented in **C** using the **SDL2 library** for graphics, **SDL2_mixer** for sound effects, and **SDL2_image** for loading images. The game supports both **single-player** (against the computer) and **multiplayer** modes, making it a fun and engaging experience for users.
---
## Examples 
![menu](https://github.com/user-attachments/assets/453044d0-c1ec-44a1-9b57-0c1f8da1f0f9)

![play](https://github.com/user-attachments/assets/e3bfc097-638a-4f8b-af3c-53a8600d347d)

---

## Features
- **Single-Player Mode**: Play against a computer that makes random moves.
- **Multiplayer Mode**: Compete with a friend on the same device.
- **Interactive GUI**: Built using SDL2 for a graphical user interface.
- **Sound Effects**: Includes sound effects for player moves, game outcomes, and menu interactions.
- **Game Over Detection**: Automatically detects when a player wins, loses, or the game ends in a tie.
- **Reset and Rematch**: Players can reset the game and play again.

---

## Technologies Used
- **Programming Language**: C
- **Libraries**:
  - **SDL2**: For graphics and window management.
  - **SDL2_mixer**: For sound effects.
  - **SDL2_image**: For loading images.
  - **SDL2_gfxPrimitives**: For rendering shapes like circles and lines.
- **Platform**: Cross-platform (Windows, Linux, macOS).

---

## How to Play
1. Launch the game.
2. Choose between **Single-Player** or **Multiplayer** mode from the main menu.
3. In Single-Player mode, the computer will make random moves.
4. In Multiplayer mode, two players take turns placing their marks (X or O) on the grid.
5. The game detects when a player wins or the game ends in a tie.
6. Press **ESC** to return to the main menu and reset the game.

---


## How to Build and Run

### Windows (Visual Studio)
1. Open the `Morpion.sln` solution file in Visual Studio.
2. Ensure that the SDL2, SDL2_mixer, SDL2_image, and SDL2_gfxPrimitives libraries are correctly linked in the project settings.
3. Build and run the project.

### Linux/Mac
1. Install the required libraries:
   ```bash
   sudo apt-get install libsdl2-dev libsdl2-mixer-dev libsdl2-image-dev
