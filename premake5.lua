workspace "FluxEngine"
    architecture "x64"
    startproject "App"

    configurations
    {
        "Debug",
        "Release"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    Includes = {}
    Includes["glfw"] = "%{wks.location}/Flux/vendor/glfw/include"
    Includes["glad"] = "%{wks.location}/Flux/vendor/glad/include"
    Includes["glm"] = "%{wks.location}/Flux/vendor/glm/include"

    group "Dependencies"
        include "Flux/vendor/glfw"
        include "Flux/vendor/glad"
    group ""

    group "Core"
        include "Flux"
        include "App"
    group ""
