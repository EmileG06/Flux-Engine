# Flux-Engine

- A modern, (hopefully) high-performance 2D and 3D game engine built with OpenGL 4.6 Core and C++23.
- This project is used as a learning experience, expect some questionable code =).

## Features

**Graphics & Rendering**
- OpenGL 4.6 Core
- Batch renderer for 2D Quads
- Platform-agnostic-ish design for eventual cross-platform compatibility

**Architecture**
- Layer/overlay system for organization and some scalability
- Event-driven architecture for input
- ImGui with dockspace support for editor UI (also useful for some debugging)

**Modern C++**
- Built with C++23 because std::println
- Clean, maintainable codebase following modern best practices (I'm trying)

## Requirements

- Visual Studio 2022
- OpenGL 4.6 capable GPU
- Premake5

## Building

```bash
# Clone the repository
git clone https://github.com/EmileG06/Flux-Engine.git --recursive

# Premake5
I didn't include the premake5 binaries in the repo, you will have to download it manually and place it in 'Flux-Engine/vendor/premake5/bin/premake5.exe'

# Generate solution files
run Generate.bat in the scripts folder

# Open solution and build
Use VS2022 minimum
```

## Acknowledgments

- [OpenGL](https://www.opengl.org/)
- [GLFW](https://www.glfw.org/)
- [GLAD](https://glad.dav1d.de/)
- [GLM](https://github.com/g-truc/glm)
- [stb_image](https://github.com/nothings/stb)
- [Dear ImGui](https://github.com/ocornut/imgui)
- [The Cherno](https://www.youtube.com/@TheCherno)
- [LearnOpenGL](https://learnopengl.com/)
- [OGLDEV](https://www.youtube.com/@OGLDEV)
- [PirateSoftware](https://youtu.be/Aq5WXmQQooo)
