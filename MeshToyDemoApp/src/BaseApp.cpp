#include "BaseApp.h"

#include "imgui.h"
#include "MeshToy/SceneObjects/Camera.h"
#include "MeshToy/SceneObjects/Grid.h"

#include "MeshToy/Utils/Gizmos.h"

BaseApp::BaseApp(): MeshToyApp({
    .WindowTitle = "TestApp",
    .WindowSize = {1920, 1080}
}) {}

void BaseApp::HandleInput(GLFWwindow* InWindow)
{

}

void BaseApp::Start()
{
    AddSceneObject<Camera>("MainCamera");
    AddSceneObject<Grid>("MainGrid");
}

void BaseApp::Update()
{
    Time += DeltaTime;
}

void BaseApp::Render()
{
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    const glm::vec2 P0(-1.0f, 0.0f);
    const glm::vec2 P1(-0.5f, 2.0f * glm::sin(Time * 2.0f));
    const glm::vec2 P2(0.5f + glm::sin(Time), 1.0f);
    const glm::vec2 P3(1.0f, 0.0f);

    Gizmos::Color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    Gizmos::DrawBezier(P0, P1, P2, P3, 0.01f);

    Gizmos::Color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    Gizmos::DrawCircle(P0, 0.02f);
    Gizmos::DrawCircle(P1, 0.02f);
    Gizmos::DrawCircle(P2, 0.02f);
    Gizmos::DrawCircle(P3, 0.02f);
    Gizmos::DrawLine(P0, P1, 0.005f);
    Gizmos::DrawLine(P2, P3, 0.005f);
    
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void BaseApp::ImGuiRender()
{
    // TODO: this should be a SceneObject
    ImGui::Begin("Control Panel");
        
    ImGui::Text("FPS: %.2f", ImGui::GetIO().Framerate);
        
    ImGui::End();
}

#pragma region Junk

// In header:
// Material MaterialScreenQuad;
// ComputeShader Compute;
// StaticMesh Rect;

// unsigned int Texture;
//
// float CurrentFrame = 0;

// TODO: move texture creation to proper class
// // ==============================================================================================================
// // CREATE TEXTURE
// // ==============================================================================================================
//
// glGenTextures(1, &Texture);
// glActiveTexture(GL_TEXTURE0);
// glBindTexture(GL_TEXTURE_2D, Texture);
//
// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 1000, 1000, 0, GL_RGBA, GL_FLOAT, nullptr);
// glBindImageTexture(0, Texture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
//
// glActiveTexture(GL_TEXTURE0);
// glBindTexture(GL_TEXTURE_2D, Texture);

// TODO: move compute shader execution to proper class
// CurrentFrame += DeltaTime;
//
// Compute.Use();
// Compute.SetFloat("t", CurrentFrame);
// glDispatchCompute(100, 100, 1);
// glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

#pragma endregion