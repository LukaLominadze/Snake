# Snake
This is a snake game made with my [C++ game engine](https://github.com/LukaLominadze/NigoziEngine).

Features:
- Controls: WASD
- Resizable window with fullscreen functionality
- Batch rendering
- ECS
- YAML for level creation

<img width="1280" alt="snake-preview" src="https://github.com/user-attachments/assets/68231d98-0d2f-4600-83e0-7388969aa444" />

![ezgif-69d3a97289b486](https://github.com/user-attachments/assets/b5d94891-0b45-4b71-8d2a-e476bc2d7916)

## Platform
This project is primarly supported on Windows

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
clone the repository with ```git clone --recursive https://github.com/LukaLominadze/Snake``` and build the project with ```setup-windwos.bat```.

If you don't want to build for visual studio, you will have to run the following command from the root directory: ```NigoziEngine\vendor\bin\scripts\premake\premake5 [action]```
feel free to run ```NigoziEngine\vendor\bin\scripts\premake\premake5 --help``` to choose the appropriate action.

Otherwise, run and build with visual studio.

## Make your levels!
The metadeta for levels exist in YAML files, which gives the ability to freely add and mutate stages.
Go to ```Snake\src\assets\levels``` and add a file with ".yaml" extensions.
Use this template to build levels:
```yaml
Level:
  Assets:
    Wall:
      Path: src/assets/sprites/wall.png # wall sprite path
      Color: [0.0, 0.0, 1.0, 1.0] # wall sprite color
    Floor:
      Path: src/assets/sprites/floor.png # floor sprite path
      Color: [1.0, 0.9, 0.4, 1.0] # floor sprite color
  Width: 12 # map width
  Height: 12 # map height
  PointsToWin: 5
  # 0 - Floor; 1 - Wall; 2 - Player
  Map:
    [ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 ]
```
