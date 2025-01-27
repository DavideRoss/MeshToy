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
    void ImGuiRender() override;

private:
    float Scale = 1.0f;

    std::shared_ptr<Mesh> TestMesh = nullptr;
};
