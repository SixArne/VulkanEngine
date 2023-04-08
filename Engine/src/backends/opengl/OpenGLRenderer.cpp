#include "OpenGLRenderer.h"
#include "core/logger/Log.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void OpenGLRenderer::Init()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        F_LOG_CORE_ERROR("Failed to initialize GLAD");
    }
}

void OpenGLRenderer::Shutdown()
{
    F_LOG_CORE_INFO("OpenGLRenderer::Shutdown()");
}

void OpenGLRenderer::Render()
{
    F_LOG_CORE_INFO("OpenGLRenderer::Draw()");
}

void OpenGLRenderer::Clear()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}