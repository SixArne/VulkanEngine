#include "Window.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "core/logger/Log.h"
#include "backends/opengl/OpenGLRenderer.h"
#include "core/scene/SceneManager.h"

Window::Window(const WindowCreateInfo& info)
{
    // Initialize GLFW
    if (glfwInit() == GLFW_FALSE)
    {
        F_LOG_CORE_ERROR("Failed to initialize GLFW");
    }

    // Create window and automatic destroy it when the window is destroyed
    m_Window = std::unique_ptr<GLFWwindow, std::function<void(GLFWwindow*)>>
    (
        glfwCreateWindow(info.width, info.height, info.title, nullptr, nullptr),
        [](GLFWwindow* window) {
            glfwDestroyWindow(window);
            F_LOG_CORE_INFO("Window destroyed");
        }
    );

    if (m_Window == nullptr)
    {
        F_LOG_CORE_ERROR("Failed to create window");
        glfwTerminate();
    }

    glfwMakeContextCurrent(m_Window.get());

    CreateRenderer(info.api);

    F_LOG_CORE_INFO("GLFW intialized and window created.");
}

void Window::CreateRenderer(GraphicsAPI api)
{
    switch (api)
    {
    case GraphicsAPI::OpenGL:
        m_Renderer = std::make_unique<OpenGLRenderer>();
        break;
    case GraphicsAPI::Vulkan:
        F_LOG_CORE_ERROR("Vulkan not supported yet");
        break;
    case GraphicsAPI::DirectX:
        F_LOG_CORE_ERROR("DirectX not supported yet");
        break;
    }

    m_Renderer->Init();
}

void Window::Run()
{
    auto& sceneManager = SceneManager::GetInstance();

    double lag{0.0};
    double fixedTimeStepSec{0.01666666666666666666666666666667};
    double desiredFPS{144.0};
    double desiredFrameTime{1.0 / desiredFPS};

    auto lastTime = std::chrono::high_resolution_clock::now();

    sceneManager.Init();
    while (!glfwWindowShouldClose(m_Window.get()))
    {
        const auto currentTime = std::chrono::high_resolution_clock::now();
        const auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count();

        m_Renderer->Clear();

        while (lag >= fixedTimeStepSec)
        {
            sceneManager.FixedUpdate(fixedTimeStepSec);
            lag -= fixedTimeStepSec;
        }
        sceneManager.Update(deltaTime);

        m_Renderer->Render();
        sceneManager.RenderImGui();

        glfwSwapBuffers(m_Window.get());
        glfwPollEvents();

        const auto sleepTime = currentTime + std::chrono::milliseconds(static_cast<int>(desiredFrameTime)) - std::chrono::high_resolution_clock::now();
        if (sleepTime > std::chrono::milliseconds(0))
        {
            std::this_thread::sleep_for(sleepTime);
        }
    }

    glfwTerminate();
}