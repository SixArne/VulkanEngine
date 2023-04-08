#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include "backends/IRenderer.h"

class OpenGLRenderer final : public IRenderer
{
public:
    virtual void Init() override;
    virtual void Shutdown() override;
    virtual void Render() override;
    virtual void Clear() override;
};

#endif
