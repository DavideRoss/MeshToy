include "Dependencies.lua"

workspace "MeshToy"
    architecture "x86_64"
    startproject "MeshToy"

    configurations
    {
        "Debug",
        "Release"
    }

    filter "configurations:Debug"
        symbols "On"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Core"
    include "MeshToy"
group ""

group "Applications"
    include "MeshToyDemoApp"
group ""

group "Data"
    include "MeshToyData"
group ""

