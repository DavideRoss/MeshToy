project "MeshToy"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    debugdir ("%{wks.location}/MeshToyData")

    files
    {
        "src/**.h",
        "src/**.cpp",
        "vendor/glad/glad.c",

        "vendor/imgui/*.h",
        "vendor/imgui/*.cpp",
        "vendor/imgui/backends/imgui_impl_glfw.*",
        "vendor/imgui/backends/imgui_impl_opengl3.*",
        "vendor/imgui/misc/cpp/imgui_stdlib.*" -- std::string support    
    }

    includedirs
    {
        "src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.GLM}",
        "%{IncludeDir.ImGUI}",
        "%{IncludeDir.ImGUIBackends}",
        "%{IncludeDir.STB}",
        "%{IncludeDir.YAML}"
    }

    defines
    {
        "GLFW_INCLUDE_NONE",
        "YAML_CPP_STATIC_DEFINE"
    }

    filter "system:windows"
        links
        {
            "%{Library.YAML}",
            "%{Library.GLFW}",
        }

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        runtime "Release"
        optimize "On"