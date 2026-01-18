# Flux-Engine

A modern, high-performance 2D game engine built with OpenGL 4.6 Core and C++23.

## Features

**Graphics & Rendering**
- OpenGL 4.6 Core for modern, efficient rendering
- Batch renderer for optimized draw call performance
- Platform-agnostic design for cross-platform compatibility

**Architecture**
- Layer-based system for organized scene management
- Event-driven architecture for responsive input and system communication
- ImGui integration with dockspace support for powerful editor UI

**Modern C++**
- Built with C++23 for cutting-edge language features
- Clean, maintainable codebase following modern best practices

## Requirements

- C++23 compatible compiler (GCC 13+, Clang 16+, or MSVC 2022+)
- OpenGL 4.6 capable GPU
- CMake 3.20 or higher (recommended)

## Building

```bash
# Clone the repository
git clone https://github.com/EmileG06/Flux-Engine.git --recursive

# Generate solution files
run Generate.bat in the scripts folder

# Open solution and build
Use VS2022 minimum
```

## Architecture Overview

**Layer System**: Organize your application into modular layers that can be pushed and popped from the layer stack. Each layer receives update, render, and event callbacks.

**Event System**: A flexible event dispatcher that propagates events through the layer stack, supporting event blocking and filtering.

**Batch Renderer**: Automatically batches draw calls to minimize state changes and maximize rendering performance.

**ImGui Editor**: Built-in dockable ImGui interface for creating custom editor tools and debug visualizations.

## Acknowledgments

- [OpenGL](https://www.opengl.org/)
- [GLFW](https://www.glfw.org/)
- [GLAD](https://glad.dav1d.de/)
- [GLM](https://github.com/g-truc/glm)
- [stb_image](https://github.com/nothings/stb)
- [Dear ImGui](https://github.com/ocornut/imgui)
- [The Cherno](https://www.youtube.com/@TheCherno)
