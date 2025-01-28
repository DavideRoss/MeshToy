#include "MeshToyApp.h"

#include <ranges>
#include <glad/glad.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "SceneObjects/Camera.h"
#include "SceneObjects/Grid.h"

#include "Utils/Log.h"

float MeshToyApp::DeltaTime = 0.0f;
int MeshToyApp::WindowWidth = 0;
int MeshToyApp::WindowHeight = 0;

MeshToyApp::MeshToyApp()
    : Settings({}) {}

MeshToyApp::MeshToyApp(MeshToyAppSettings InSettings)
    : Settings(std::move(InSettings))
{
    WindowWidth = Settings.WindowSize.x;
    WindowHeight = Settings.WindowSize.y;
    
    InitializeGLFW();
    InitializeGLAD();
    InitializeImGui();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(Settings.ClearColor.x, Settings.ClearColor.y, Settings.ClearColor.z, 1.0f);

    AddSceneObject<Camera>("MainCamera");
    AddSceneObject<Grid>("MainGrid");
}

MeshToyApp::~MeshToyApp()
{
    Destroy();
}

void MeshToyApp::Start()
{
    for (const std::shared_ptr<SceneObject>& SceneObject : SceneObjects | std::views::values)
    {
        SceneObject->Start();
    }
}

void MeshToyApp::Run()
{
    while (!glfwWindowShouldClose(Window))
    {
        const float CurrentFrame = static_cast<float>(glfwGetTime());
        DeltaTime = CurrentFrame - LastFrame;
        LastFrame = CurrentFrame;

        for (const std::shared_ptr<SceneObject>& SceneObject : SceneObjects | std::views::values)
        {
            SceneObject->Update();
        }
        
        HandleInput_Internal();

        Update();
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        
        ImGui::NewFrame();
        
        RenderImGui_Internal();
        ImGuiRender();

        for (const std::shared_ptr<SceneObject>& SceneObject : SceneObjects | std::views::values)
        {
            SceneObject->RenderImGui();
        }
        
        ImGui::Render();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (const std::shared_ptr<SceneObject>& SceneObject : SceneObjects | std::views::values)
        {
            SceneObject->Render();
        }

        Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(Window);
        glfwPollEvents();

        // TODO: maybe not needed?
        std::cout << std::flush;
    }
}

void MeshToyApp::Destroy() const
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(Window);
    glfwTerminate();
}

void MeshToyApp::InitializeGLFW()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    Window = glfwCreateWindow(
        Settings.WindowSize.x, Settings.WindowSize.y,
        Settings.WindowTitle.c_str(),
        nullptr, nullptr
    );
    
    if (Window == nullptr)
    {
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(Window);
    glfwSetFramebufferSizeCallback(Window, FrameBufferSizeCallback);
}

void MeshToyApp::InitializeGLAD()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }
}

void MeshToyApp::InitializeImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& IO = ImGui::GetIO(); (void)IO;
    IO.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    IO.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(Window, true);
    ImGui_ImplOpenGL3_Init("#version 150");
}

void MeshToyApp::FrameBufferSizeCallback(GLFWwindow* InWindow, const int Width, const int Height)
{
    WindowWidth = Width;
    WindowHeight = Height;
    glViewport(0, 0, Width, Height);
}

void MeshToyApp::HandleInput_Internal()
{
    glfwPollEvents();
    if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(Window, true);
    }

    for (const auto& SceneObject : SceneObjects | std::views::values)
    {
        SceneObject->HandleInput(Window);
    }

    HandleInput(Window);
}

void MeshToyApp::RenderImGui_Internal()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Scene Objects"))
        {
            // TODO: add toggles for scene objects windows in here
            ImGui::MenuItem("Test 1234");
            ImGui::EndMenu();
        }
        
        ImGui::EndMainMenuBar();
    }
}
