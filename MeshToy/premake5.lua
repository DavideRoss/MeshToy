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
        "%{IncludeDir.ImGUIBackends}"
    }

    defines
    {
        "GLFW_INCLUDE_NONE"
    }

    filter "system:windows"
        links
        {
            "%{Library.GLFW}"
        }