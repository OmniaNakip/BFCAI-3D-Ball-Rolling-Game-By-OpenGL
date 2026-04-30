# 3D-Ball Rolling Game By OpenGL

A 3D Ball Rolling Game built using OpenGL as a team project for BFCAI students. The game features a controllable ball moving in a 3D environment with obstacles, camera system, lighting, textures, and collision detection.

## About

This project was developed at the **Faculty of Computers and Artificial Intelligence, Benha University** — **AI Department**, **3rd Level**.

## Team Members

- Ahmed Hazem Elabady
- Ahmed Badwy
- Alaa Osama Mohamed Bekhit
- Abanoub Rizk Gad
- Abdelrahman Reda Abdelrahman Abdelstar
- Omnia Mohamed Ahmed Naqeeb

## How to Start and Test

Since the project is currently in development, follow these steps to set up the environment and test the current progress:

### 1. Prerequisites
- **Visual Studio 2019 or 2022** with "Desktop development with C++" workload installed.

### 2. Opening the Project
- Open `3d_ball_rolling_game/3d_ball_rolling_game.sln`.

### 3. Fixing Project Paths
The project may contain absolute paths that need to be updated for your local machine:
- **Right-click** the project in Solution Explorer -> **Properties**.
- Under **C/C++ -> General -> Additional Include Directories**, ensure these exist:
  - `$(ProjectDir)external\GLAD\include`
  - `$(ProjectDir)external\glfw-3.4.bin.WIN64\include`
  - `$(ProjectDir)`
- Under **Linker -> General -> Additional Library Directories**, ensure it points to:
  - `$(ProjectDir)external\glfw-3.4.bin.WIN64\lib-vc2022` (or your version).

### 4. Running the App
- Set the solution configuration to **Debug** and the platform to **x64**.
- Press **F5** to build and run.

*Note: As this is a work-in-progress, the main scene integration and shaders are currently being finalized. To see a demo of the current geometry, ensure placeholder shaders are present in the `assets/shaders` folder.*
