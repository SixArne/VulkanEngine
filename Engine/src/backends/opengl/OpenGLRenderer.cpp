#include "OpenGLRenderer.h"
#include "core/logger/Log.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "utils/File.h"
#include "core/loaders/images/ImageLoader.h"
#include "core/loaders/meshes/MeshLoader.h"

void OpenGLRenderer::Init()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        F_LOG_CORE_ERROR("Failed to initialize GLAD");
    }

    m_ShaderProgram = LoadShader(
        "resources/shaders/opengl/DiffuseShader.vert",
        "resources/shaders/opengl/DiffuseShader.frag"
    );

    auto image = ImageLoader::GetInstance().Load("resources/images/test.jpg");
    auto mesh = MeshLoader::GetInstance().Load("resources/meshes/Chair.obj");

    glGenVertexArrays(1, &m_VertexArray);
    glGenBuffers(1, &m_VertexBuffer);
    glGenBuffers(1, &m_IndexBuffer);

    // ... (Set up the vertex data for your objects and store it in the VBO and EBO)

}

void OpenGLRenderer::Shutdown()
{
    glDeleteProgram(m_ShaderProgram);
    glDeleteVertexArrays(1, &m_VertexArray);
    glDeleteBuffers(1, &m_VertexBuffer);
    glDeleteBuffers(1, &m_IndexBuffer);

    F_LOG_CORE_INFO("OpenGLRenderer::Shutdown()");
}

void OpenGLRenderer::Render()
{


    F_LOG_CORE_INFO("OpenGLRenderer::Draw()");
}

void OpenGLRenderer::Clear()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLuint OpenGLRenderer::LoadShader(const std::string &vertexPath, const std::string &fragmentPath)
{
    // Read vertex shader code
    std::string vertexCode = ReadFileContent(vertexPath);

    // Read fragment shader code
    std::string fragmentCode = ReadFileContent(fragmentPath);

    // Create shader objects
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Compile shaders
    CompileShader(vertexShader, vertexCode.c_str());
    CompileShader(fragmentShader, fragmentCode.c_str());

    // Create shader program
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // Check for linking errors
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        F_LOG_CORE_ERROR("ERROR::SHADER::PROGRAM::LINKING_FAILED {}", infoLog);
    }

    // Delete the shaders as they are linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

void OpenGLRenderer::CompileShader(GLuint shader, const char* source)
{
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);


    // Check for compilation errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        F_LOG_CORE_ERROR("ERROR::SHADER::VERTEX::COMPILATION_FAILED {}", infoLog);
    }
}
