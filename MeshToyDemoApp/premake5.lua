project "MeshToyDemoApp"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    debugdir ("%{wks.location}/MeshToyData")

    files
	{
		"src/**.h",
		"src/**.cpp"
	}

    includedirs
    {
        "%{wks.location}/MeshToy/src",
        "%{wks.location}/MeshToy/vendor",
        
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.GLM}",
        "%{IncludeDir.ImGUI}",
        "%{IncludeDir.ImGUIBackends}",
        "%{IncludeDir.STB}",
        "%{IncludeDir.YAML}"
    }

    links
    {
        "MeshToy"
    }
