#include "Camera.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include "imgui.h"
#include "MeshToy/MeshToyApp.h"

void Camera::Start()
{
    glGenBuffers(1, &UBO);
    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    // TODO: use a struct instead?
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) * 2, nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, UBO, 0, sizeof(glm::mat4) * 2);

    UpdateMatrices(true);
}

void Camera::Update()
{
    UpdateMatrices();
}

void Camera::HandleInput(GLFWwindow* Window)
{
    glm::vec2 DeltaOffset(
        glfwGetKey(Window, GLFW_KEY_A) - glfwGetKey(Window, GLFW_KEY_D),
        glfwGetKey(Window, GLFW_KEY_S) - glfwGetKey(Window, GLFW_KEY_W)
    );

    if (glm::length(DeltaOffset) > 0)
    {
        Offset += DeltaOffset * Speed * MeshToyApp::DeltaTime;
        bDirty = true;
    }

    float LastExtent = Extent;
    Extent = glm::clamp(
        Extent + static_cast<float>(glfwGetKey(Window, GLFW_KEY_Q) - glfwGetKey(Window, GLFW_KEY_E)) * Speed * MeshToyApp::DeltaTime,
        0.1f,
        20.0f
    );

    // TODO: use something like if(std::abs(v1-v2)<0.01) (put on a utils class)
    if (LastExtent != Extent) bDirty = true;
}

void Camera::RenderImGui()
{
    ImGui::Begin("Camera");

    ImGui::Text("Position:");
    ImGui::SameLine(100);
    ImGui::Text(glm::to_string(Offset).c_str());

    ImGui::Text("Extent:");
    ImGui::SameLine(100);
    ImGui::Text(std::to_string(Extent).c_str());

    bool bResetAll = ImGui::Button("Reset All");
    ImGui::SameLine();

    if (ImGui::Button("Set to (0, 0)") || bResetAll)
    {
        Offset = glm::vec2(0.0f);
        bDirty = true;
    }

    ImGui::SameLine();

    if (ImGui::Button("Reset Extent") || bResetAll)
    {
        Extent = 2.0f;
        bDirty = true;
    }

    ImGui::End();
}

void Camera::UpdateMatrices(const bool bForce)
{
    if (!bForce && !bDirty) return;

    const float AspectRatio = static_cast<float>(MeshToyApp::WindowWidth) / static_cast<float>(MeshToyApp::WindowHeight);
    const float Half = Extent * AspectRatio;
    
    Projection = glm::ortho(
        -Half, Half, -Extent, Extent,
        NearPlane, FarPlane
    );

    View = glm::translate(glm::mat4(1.0f), glm::vec3(Offset.x, Offset.y, -5.0f));

    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(Projection));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(View));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
