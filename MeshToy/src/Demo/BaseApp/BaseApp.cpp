#include "BaseApp.h"

#include "imgui.h"

#include "MeshToy/SceneObjects/Mesh.h"
#include "MeshToy/Shapes/Quad.h"

BaseApp::BaseApp(): MeshToyApp({
    .WindowTitle = "TestApp",
    .WindowSize = {1920, 1080}
}) {}

void BaseApp::HandleInput(GLFWwindow* InWindow)
{
    if (glfwGetKey(InWindow, GLFW_KEY_R) == GLFW_PRESS)
    {
        Scale += 1.0f * MeshToyApp::DeltaTime;
    }

    if (glfwGetKey(InWindow, GLFW_KEY_T) == GLFW_PRESS)
    {
        Scale -= 1.0f * MeshToyApp::DeltaTime;
    }
}

void BaseApp::Start()
{
    const Quad TestQuad;

    Texture* CheckerTex = new Texture("textures/checker.png");
    Material* QuadMaterial = new Material("Unlit_Texture");
    QuadMaterial->Use();
    
    QuadMaterial->SetVector4("BaseColor", 1.0f, 1.0f, 1.0f, 1.0f);
    QuadMaterial->SetTexture("Texture", CheckerTex);

    TestMesh = AddSceneObject<Mesh>("TestQuad", TestQuad.BuildStaticMesh(), QuadMaterial);
}

void BaseApp::Update()
{
    TestMesh->SetScale(glm::vec3(Scale));
}

void BaseApp::ImGuiRender()
{
    // TODO: this should be a sceneobject
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