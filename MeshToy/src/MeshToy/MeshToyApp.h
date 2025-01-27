#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <GLFW/glfw3.h>

#include "SceneObjects/SceneObject.h"

struct MeshToyAppSettings
{
    std::string WindowTitle = "MeshToy App";
    glm::ivec2 WindowSize = { 800, 600 };
    glm::vec3 ClearColor = glm::vec3(0.137f, 0.207f, 0.32f);
};

class MeshToyApp
{
public:
    MeshToyApp();
    MeshToyApp(MeshToyAppSettings InSettings);
    virtual ~MeshToyApp();

public:
    void Run();
    void Destroy() const;

    virtual void Start();
    virtual void Update() {}
    virtual void ImGuiRender() {}
    virtual void Render() {}

    virtual void HandleInput(GLFWwindow* InWindow) {}

    template<typename T, typename... Args>
    std::shared_ptr<T> AddSceneObject(const std::string& InName, Args&&... Arguments)
    {
        static_assert(std::is_base_of_v<SceneObject, T>, "T must derive from SceneObject");

        // TODO: ensure name uniqueness

        std::shared_ptr<T> NewSceneObject = std::make_shared<T>(InName, std::forward<Args>(Arguments)...);
        SceneObjects.insert({ InName, NewSceneObject });
        NewSceneObject->Start();
        
        return NewSceneObject;
    }

private:
    void InitializeGLFW();
    void InitializeGLAD();
    void InitializeImGui();

    static void FrameBufferSizeCallback(GLFWwindow* InWindow, int Width, int Height);
    void HandleInput_Internal();

    void RenderImGui_Internal();

// Static variables
public:
    static float DeltaTime;
    static int WindowWidth;
    static int WindowHeight;

private:
    MeshToyAppSettings Settings;
    GLFWwindow* Window = nullptr;
    
    float LastFrame = 0.0f;
    
    std::unordered_map<std::string, std::shared_ptr<SceneObject>> SceneObjects;
};
