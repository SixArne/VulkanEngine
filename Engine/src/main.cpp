#include <iostream>
#include "ecs\Component.h"
#include "ecs\GameObject.h"
#include <GLFW/glfw3.h>

int main()
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GameObject go;
    Transform* test = go.AddComponent<Transform>();

    std::cout << test->GetName() << std::endl;
}