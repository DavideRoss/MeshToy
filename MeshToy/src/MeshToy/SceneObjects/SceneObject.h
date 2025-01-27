#pragma once

#include <string>

#include <GLFW/glfw3.h>

class SceneObject
{
public:
    SceneObject(std::string InName) : Name(std::move(InName)) { }
    virtual ~SceneObject() = default;

    virtual void Start() {}
    virtual void Update() {}
    virtual void Render() {}
    virtual void RenderImGui() {}
    virtual void HandleInput(GLFWwindow* Window) {}

public:
    std::string Name;
};
