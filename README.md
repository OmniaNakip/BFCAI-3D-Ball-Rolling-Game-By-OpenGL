# EndlessRunner3D

A simple 3D endless runner prototype built with C++ and OpenGL/GLUT.

## Structure
- src/ : C++ implementation files
- include/ : headers
- assets/ : textures and sounds (future milestones)

## Build (example)
Install a GLUT distribution (e.g., freeglut) and make sure the libraries are available.

### MinGW (example)
g++ src/*.cpp -Iinclude -lfreeglut -lopengl32 -lglu32 -o EndlessRunner3D

### Visual Studio
Create a console project, add all src/*.cpp, add include/ to include dirs,
and link against OpenGL32.lib, Glu32.lib, and freeglut.lib (or glut32.lib).

## Controls
- Enter: start
- A/D or Left/Right: change lane
- Space or Up: jump
- R: restart after Game Over
- Esc: quit
