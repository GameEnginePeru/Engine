project "Engine"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "On"

    targetdir("../bin/" .. outputdir .. "/%{prj.name}")
    objdir("../bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "src",
        "vendor/GLFW/include",
        "vendor/glew/include",
        "vendor/glm"
    }

    libdirs
    {
        "vendor/glew/lib"
    }

    links
    {
        "GLFW",
        "opengl32.lib",
        "glew32s.lib"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines "PE_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "PE_RELEASE"
        runtime "Release"
        optimize "on"
    
    filter "configurations:Dist"
        defines "PE_DIST"
        runtime "Release"
        optimize "on"