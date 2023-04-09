#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include <string>
#include "backends/IRenderer.h"
#include <glad/glad.h>


class OpenGLRenderer final : public IRenderer
{
public:
    virtual void Init() override;
    virtual void Shutdown() override;
    virtual void Render() override;
    virtual void Clear() override;

private:
    GLuint LoadShader(const std::string& vertexPath, const std::string& fragmentPath);
    void CompileShader(GLuint shader, const char* source);

    GLuint m_ShaderProgram;
    GLuint m_VertexArray;
    GLuint m_VertexBuffer;
    GLuint m_IndexBuffer;
};

#endif
