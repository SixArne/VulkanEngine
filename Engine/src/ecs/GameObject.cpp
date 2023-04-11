#include "GameObject.h"

GameObject::GameObject(const std::string& name)
    : m_Name(name)
{
}

const std::string& GameObject::GetName() const
{
    return m_Name;
}

void GameObject::Init()
{
    for (const auto& component : m_Components)
        component.second->Init();
}

void GameObject::Shutdown()
{
    for (const auto& component : m_Components)
        component.second->Shutdown();
}

void GameObject::Update(double deltaTime)
{
    for (const auto& component : m_Components)
        component.second->Update(deltaTime);
}

void GameObject::FixedUpdate(double fixedDeltaTime)
{
    for (const auto& component : m_Components)
        component.second->FixedUpdate(fixedDeltaTime);
}

void GameObject::RenderImGui()
{
    for (const auto& component : m_Components)
        component.second->RenderImGui();
}

void GameObject::LateUpdate(double fixedDeltaTime)
{
    for (const auto& component : m_Components)
        component.second->LateUpdate(fixedDeltaTime);
}

void GameObject::Render()
{
    for (const auto& component : m_Components)
        component.second->Render();
}
