# Snake
This is a snake game made with my [C++ game engine](https://github.com/LukaLominadze/NigoziEngine/tree/dev).

Features:
- Controls: WASD
- Resizable window with fullscreen functionality
- Batch rendering
- ECS
- YAML for level creation

## The game in action!

![ezgif-69d3a97289b486](https://github.com/user-attachments/assets/b5d94891-0b45-4b71-8d2a-e476bc2d7916)

## Level editor!

![ezgif-82f9eb3682b54e](https://github.com/user-attachments/assets/8b18cb0b-559b-4ce6-a834-ebf429790665)

## Platform
This project is primarly supported on Windows and Linux (Ubuntu LTS 24.04.02 Tested)

## Dependencies
Note: The dependencies are handled with the repository's build system
- [NigoziEngine](https://github.com/LukaLominadze/NigoziEngine)
- GLFW
- OpenGL (GLEW)
- ImGui
- STB
- YAML
- entt

## Building
clone the repository with ```git clone --recursive https://github.com/LukaLominadze/Snake```

### Windows
To build the project, run ```setup-windows.bat```.

If you don't want to build for visual studio, you will have to run the following command from the root directory: ```NigoziEngine\vendor\bin\scripts\premake\premake5 [action]```
feel free to run ```NigoziEngine\vendor\bin\scripts\premake\premake5 --help``` to choose the appropriate action.

Otherwise, run and build with visual studio.
### Linux (Ubuntu LTS 24.04.02 Tested)
To build the project, run ```setup-linux.sh``` and then run ```make```.
 Optionally, run ```make config={CONFIG} # config can be debug/release/distribution```.

The build will be located in the generated ```bin``` directory.

## Make your levels!
Open up the game and go to Editor -> New (or "Load" to mutate existing levels)

Options:
- Wall texture - Change the wall texture
- Floor texture - Change the floor texture
- Brush - Draw walls on the map
- Eraser - Erase walls on the map
- Player - Choose the player's spawn position
On ImGui window:
- Level name
- Wall color
- Floor color
- Points To Win
- Save existing level
- Save as a copy

<img width="1602" height="932" alt="image" src="https://github.com/user-attachments/assets/3228fee4-c093-422b-8ad3-66b9ff2365be" />

