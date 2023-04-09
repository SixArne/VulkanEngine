#include "Window.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "core/logger/Log.h"
#include "backends/opengl/OpenGLRenderer.h"

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
    while (!glfwWindowShouldClose(m_Window.get()))
    {
        m_Renderer->Clear();

        glfwSwapBuffers(m_Window.get());
        glfwPollEvents();
    }

    glfwTerminate();
}