
# Flux-Engine

A modern 2D and 3D game engine built with OpenGL 4.6 Core and C++23

# Disclaimer

This project is strongly inspired by TheCherno’s game engine series. The goal is to expand on it by adding 3D support and my own ideas along the way.

I’m not claiming this as a fully original engine built from scratch. This project is primarily a learning and experimentation space, where I explore engine architecture and graphics concepts. It’s not meant to demonstrate a finished or fully independent engine, just the process of learning and improving.

## Features

**Graphics & Rendering**
- 2D quads using batch rendering
- 3D rendering (currently only hard coded meshes)

**Architecture**
- Layer/overlay system
- Events that can propagate (window, keyboard, mouse)
- Entity component system using entt
- Native scripting

**Editor (WIP)**
- Uses Dear ImGui for user interface
- Dockable/resizable panels
- Create/Delete entity
- Create/Delete component

**Components**
- Tag Component
- Transform Component
- Mesh Component
- Native Script Component

## Requirements

- Visual Studio 2022/2026
- OpenGL 4.6 capable GPU
- Premake5

## Building

```
- Clone the repository
git clone https://github.com/EmileG06/Flux-Engine.git --recursive

- Premake5
I didn't include the premake5 binaries in the repo,
you will have to download it manually and place it in 'Flux-Engine/vendor/premake5/bin/premake5.exe'
If the directory doesn't exist, create it manually

- Generate solution files
run Generate.bat in the scripts folder

- Build
Open solution file with Visual Studio and build the solution
```

## Acknowledgments

- [OpenGL](https://www.opengl.org/)
- [GLFW](https://www.glfw.org/)
- [GLAD](https://glad.dav1d.de/)
- [GLM](https://github.com/g-truc/glm)
- [stb_image](https://github.com/nothings/stb)
- [Dear ImGui](https://github.com/ocornut/imgui)
- [tinygltf](https://github.com/syoyo/tinygltf)
- [entt](https://github.com/skypjack/entt)
- [yaml-cpp](https://github.com/jbeder/yaml-cpp)
- [The Cherno](https://www.youtube.com/@TheCherno)
- [LearnOpenGL](https://learnopengl.com/)
- [OGLDEV](https://www.youtube.com/@OGLDEV)
