#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

class GameObject;

class Component
{
public:
    virtual ~Component() = default;
    virtual std::string GetName(){ return std::string("component");};

    virtual void Init() {};
    virtual void Shutdown() {};
    virtual void Render() {};
    virtual void Update(double deltaTime) = 0;
    virtual void FixedUpdate(double fixedDeltaTime) {};
    virtual void RenderImGui() {};
    virtual void LateUpdate(double fixedDeltaTime) {};

protected:
    Component() {};
    explicit Component(GameObject* pOwner);
    inline GameObject* GetOwner() const;

private:
    GameObject* m_pOwner;
};

#endif