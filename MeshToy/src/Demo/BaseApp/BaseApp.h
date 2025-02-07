#pragma once

#include "MeshToy/MeshToyApp.h"

class BaseApp : public MeshToyApp
{
public:
    BaseApp();

    void HandleInput(GLFWwindow* InWindow) override;
    void Start() override;
    void Update() override;
    void Render() override;
    void ImGuiRender() override;
};
