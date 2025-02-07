#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/detail/type_quat.hpp>

#include "SceneObject.h"

// https://github.com/emeiri/ogldev/blob/master/Include/ogldev_glm_camera.h
class Camera3D : public SceneObject
{
public:
    // TODO: add perspective settings
    explicit Camera3D(
        const std::string& InName,
        const glm::vec3& InPosition = glm::vec3(0.0f),
        const glm::vec3& InUp = glm::vec3(0.0f, 1.0f, 0.0f),
        const glm::vec3& Target = glm::vec3(0.0f)
    );

    void Start() override;
    void Update() override;
    void HandleInput(GLFWwindow* Window) override;
    void RenderImGui() override;

private:
    void UpdateMatrices(bool bForce = false);

private:
    bool bDirty = false;

    glm::mat4 Projection = glm::mat4(1.0f);
    glm::mat4 View = glm::mat4(1.0f);

    unsigned int UBO = 0;

    glm::vec3 Position;
    glm::vec3 Up;
    glm::quat Orientation;

    float Speed = 5.0f;
};
