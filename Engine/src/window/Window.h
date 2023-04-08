#ifndef WINDOW_H
#define WINDOW_H

#include <memory>
#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "backends/IRenderer.h"

enum GraphicsAPI
{
    OpenGL,
    Vulkan,
    DirectX
};

struct WindowCreateInfo
{
    int width{800};
    int height{600};
    const char* title{"Window title"};
    GraphicsAPI api{GraphicsAPI::Vulkan};
};

class Window
{
public:
    Window(const WindowCreateInfo& info);
    ~Window() = default;

    void Run();
    void CreateRenderer(GraphicsAPI api);

private:
    std::unique_ptr<IRenderer> m_Renderer;
    std::unique_ptr<GLFWwindow, std::function<void(GLFWwindow*)>> m_Window;
};

#endif
