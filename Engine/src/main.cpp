#include <vld.h>
#include <iostream>
#include "core/logger/Log.h"
#include "window/Window.h"

int main()
{
    // Initialize logger
    Log::Init();

    // Create window info
    WindowCreateInfo info{};
    info.width = 800;
    info.height = 600;
    info.api = GraphicsAPI::OpenGL;
    info.title = "Engine";

    // Create window
    std::unique_ptr<Window> window = std::make_unique<Window>(info);

    // Run App
    window->Run();
}