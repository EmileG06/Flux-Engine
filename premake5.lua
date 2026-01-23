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
    Includes["stb"] = "%{wks.location}/Flux/vendor/stb"
    Includes["entt"] = "%{wks.location}/Flux/vendor/entt/single_include"
    Includes["yaml"] = "%{wks.location}/Flux/vendor/yaml-cpp/include"

    group "Dependencies"
        include "Flux/vendor/glfw"
        include "Flux/vendor/glad"
        include "Flux/vendor/imgui"
        include "Flux/vendor/yaml-cpp"
    group ""

    group "Core"
        include "Flux"
        include "Editor"
    group ""
