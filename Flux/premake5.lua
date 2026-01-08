project "Flux"
    kind "StaticLib"
    language "C++"
    cppdialect "C++23"

    toolset "v145"
    staticruntime "on"
    systemversion "latest"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin/int/" .. outputdir .. "/%{prj.name}")

    pchheader "FXPch.h"
    pchsource "src/FXPch.cpp"

    flags
    {
        "MultiProcessorCompile"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS",
        "FX_BUILD_ENGINE"
    }

    files
    {
        "src/**.h",
        "src/**.cpp",
        "%{Includes.glm}/**.hpp",
        "%{Includes.glm}/**.inl",
        "%{Includes.stb_image}/stb_image.h"
    }

    includedirs
    {
        "src",
        "%{Includes.glfw}",
        "%{Includes.glad}",
        "%{Includes.glm}",
        "%{Includes.imgui}",
        "%{Includes.stb_image}"
    }

    links
    {
        "opengl32.lib",
        "glfw",
        "glad",
        "imgui"
    }

    filter "system:windows"
        defines { "FX_PLATFORM_WINDOWS" }

    filter "configurations:Debug"
        defines { "FX_CFG_DEBUG "}
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines { "FX_CFG_RELEASE "}
        runtime "Release"
        optimize "on"