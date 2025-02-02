IncludeDir = {
    GLFW =  "%{wks.location}/MeshToy/vendor/glfw/include",
    GLAD =  "%{wks.location}/MeshToy/vendor/glad/include",
    GLM =  "%{wks.location}/MeshToy/vendor/glm",
    ImGUI = "%{wks.location}/MeshToy/vendor/imgui",
    ImGUIBackends = "%{wks.location}/MeshToy/vendor/imgui/backends",
    STB = "%{wks.location}/MeshToy/vendor/stb",
    YAML = "%{wks.location}/MeshToy/vendor/yaml-cpp/include",
}

Library = {
    GLFW = "%{wks.location}/MeshToy/vendor/glfw/lib-vc2022/glfw3.lib",
    YAML = "%{wks.location}/MeshToy/vendor/yaml-cpp/lib/yaml-cppd.lib"
}
