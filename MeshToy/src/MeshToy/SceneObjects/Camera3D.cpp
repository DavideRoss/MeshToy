#include "Camera3D.h"

#include <glad/glad.h>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.inl>
#include <glm/gtx/string_cast.hpp>

#include "imgui.h"
#include "MeshToy/MeshToyApp.h"

Camera3D::Camera3D(const std::string& InName, const glm::vec3& InPosition, const glm::vec3& InUp, const glm::vec3& Target)
    : SceneObject(InName), Position(InPosition), Up(InUp)
{
    Orientation = glm::lookAtRH(Position, Position + Target, Up);
}

// TODO: move down
void Camera3D::UpdateMatrices(const bool bForce)
{
    if (!bForce && !bDirty) return;

    const float AspectRatio = static_cast<float>(MeshToyApp::WindowWidth) / static_cast<float>(MeshToyApp::WindowHeight);

    // TODO: move FOV and near/far clipping planes to some kind of settings
    Projection = glm::perspectiveRH(60.0f, AspectRatio, 0.1f, 1000.0f);
    View = glm::mat4_cast(Orientation) * glm::translate(glm::mat4(1.0f), -Position);

    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(Projection));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(View));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Camera3D::Start()
{
    glGenBuffers(1, &UBO);
    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    // TODO: use a struct instead?
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) * 2, nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, UBO, 0, sizeof(glm::mat4) * 2);

    UpdateMatrices(true);
}

void Camera3D::Update()
{
    UpdateMatrices();
}

void Camera3D::HandleInput(GLFWwindow* Window)
{
    const glm::vec3 DeltaOffset(
        glfwGetKey(Window, GLFW_KEY_A) - glfwGetKey(Window, GLFW_KEY_D),
        glfwGetKey(Window, GLFW_KEY_S) - glfwGetKey(Window, GLFW_KEY_W),
        glfwGetKey(Window, GLFW_KEY_E) - glfwGetKey(Window, GLFW_KEY_Q)
    );

    if (glm::length(DeltaOffset) > 0)
    {
        Position += DeltaOffset * Speed * MeshToyApp::DeltaTime;
        bDirty = true;
    }

    // TODO: handle rotation
}

void Camera3D::RenderImGui()
{
    ImGui::Begin("Camera");

    ImGui::Text("Position:");
    ImGui::SameLine(120);
    ImGui::Text("%s", glm::to_string(Position).c_str());

    // TODO: 
    // ImGui::Text("Mouse:");
    // ImGui::SameLine(120);
    // ImGui::Text("%s", glm::to_string(MousePosition).c_str());

    // bool bResetAll = ImGui::Button("Reset All");
    // ImGui::SameLine();

    // TODO: cleanup
    bool bResetAll = false;

    if (ImGui::Button("Set to (0, 0)") || bResetAll)
    {
        Position = glm::vec3(0.0f);
        bDirty = true;
    }

    // ImGui::SameLine();
    //
    // if (ImGui::Button("Reset Extent") || bResetAll)
    // {
    //     Extent = 2.0f;
    //     bDirty = true;
    // }

    ImGui::End();
}
