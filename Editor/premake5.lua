project "Editor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"

    toolset "v145"
    staticruntime "on"
    systemversion "latest"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin/" .. outputdir .. "/%{prj.name}/int")

    flags
    {
        "MultiProcessorCompile"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS",
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
        "../Flux/vendor",
        "%{Includes.glm}"
    }

    links
    {
        "Flux"
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