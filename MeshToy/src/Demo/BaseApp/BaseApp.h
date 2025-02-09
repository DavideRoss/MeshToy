#pragma once

#include "MeshToy/MeshToyApp.h"

class Mesh;

class BaseApp : public MeshToyApp
{
public:
    BaseApp();

    void HandleInput(GLFWwindow* InWindow) override;
    void Start() override;
    void Update() override;
    void Render() override;
    void ImGuiRender() override;

private:
    float Time = 0.0f;
};
