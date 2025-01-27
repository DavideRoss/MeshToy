IncludeDir = {
    SDL2 =  "%{wks.location}/MeshToy/vendor/sdl2/include",
    GLFW =  "%{wks.location}/MeshToy/vendor/glfw/include",
    GLAD =  "%{wks.location}/MeshToy/vendor/glad/include",
    GLM =  "%{wks.location}/MeshToy/vendor/glm",
    ImGUI = "%{wks.location}/MeshToy/vendor/imgui",
    ImGUIBackends = "%{wks.location}/MeshToy/vendor/imgui/backends"
}

Library = {
    SDL2 = "%{wks.location}/MeshToy/vendor/sdl2/lib/x64/SDL2.lib",
    SDL2_Main = "%{wks.location}/MeshToy/vendor/sdl2/lib/x64/SDL2main.lib",
    GLFW = "%{wks.location}/MeshToy/vendor/glfw/lib-vc2022/glfw3.lib"
}
