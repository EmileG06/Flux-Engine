workspace "FluxEngine"
    architecture "x64"
    startproject "App"

    configurations
    {
        "Debug",
        "Release"
    }

    debugdir ("%{wks.location}")

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    Includes = {}
    Includes["glfw"] = "%{wks.location}/Flux/vendor/glfw/include"
    Includes["glad"] = "%{wks.location}/Flux/vendor/glad/include"
    Includes["glm"] = "%{wks.location}/Flux/vendor/glm"
    Includes["imgui"] = "%{wks.location}/Flux/vendor/imgui"
    Includes["stb_image"] = "%{wks.location}/Flux/vendor/stb_image/include"
    Includes["tinygltf"] = "%{wks.location}/Flux/vendor/tinygltf"
    Includes["entt"] = "%{wks.location}/Flux/vendor/entt"

    group "Dependencies"
        include "Flux/vendor/glfw"
        include "Flux/vendor/glad"
        include "Flux/vendor/imgui"
    group ""

    group "Core"
        include "Flux"
        include "Editor"
    group ""
