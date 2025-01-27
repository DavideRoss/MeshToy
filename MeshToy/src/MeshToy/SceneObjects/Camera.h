#pragma once

#include <glm/glm.hpp>

#include "SceneObject.h"

class Camera : public SceneObject
{
public:
    explicit Camera(const std::string& InName) : SceneObject(InName) {}

    void Start() override;
    void Update() override;
    void HandleInput(GLFWwindow* Window) override;
    void RenderImGui() override;
    
    glm::mat4 GetViewMatrix() const { return View; }
    glm::mat4 GetProjectionMatrix() const { return Projection; }

private:
    void UpdateMatrices(bool bForce = false);

private:
    glm::mat4 Projection  = glm::mat4(1.0f);
    glm::mat4 View = glm::mat4(1.0f);

    unsigned int UBO = 0;

    bool bDirty = false;

    // TODO: zoom with projection, move with view
    float Speed = 5.0f;
    glm::vec2 Offset = glm::vec2(0.0f);
    float Extent = 2.0f;
    float NearPlane = 0.1f;
    float FarPlane = 100.0f;
};
