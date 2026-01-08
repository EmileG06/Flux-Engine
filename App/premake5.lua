project "App"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"

    toolset "v145"
    staticruntime "on"
    systemversion "latest"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin/int/" .. outputdir .. "/%{prj.name}")

    flags
    {
        "MultiProcessorCompile"
    }

    defines
    {
        "FX_BUILD_APP"
    }

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "src",
        "../Flux/src",
        "%{Includes.glm}"
    }

    links
    {
        "Flux"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"