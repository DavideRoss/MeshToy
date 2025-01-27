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

include "MeshToy"
include "MeshToyData"
