#ifndef RENDERER_H
#define RENDERER_H

//TODO - Look into CRTP (Curiously Recurring Template Pattern) for this class
class IRenderer
{
public:
    virtual void Init() = 0;
    virtual void Shutdown() = 0;
    virtual void Render() = 0;
    virtual void Clear() = 0;

    //FIXME - Extract to scene
    virtual void Update(double deltaTime) = 0;
    virtual void FixedUpdate(double fixedDeltaTime) = 0;
    virtual void RenderImGui() = 0;
    virtual void LateUpdate(double fixedDeltaTime) = 0;
};

#endif
