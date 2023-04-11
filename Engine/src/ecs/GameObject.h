#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <unordered_map>
#include <vector>
#include <memory>
#include <typeindex>
#include "Component.h"


template<typename T>
concept ComponentType = std::is_base_of<Component, T>::value;

class GameObject final
{
public:
    GameObject(const std::string& name);
    ~GameObject() = default;

    void Init();
    void Shutdown();
    void Render();
    void Update(double deltaTime);
    void FixedUpdate(double fixedDeltaTime);
    void RenderImGui();
    void LateUpdate(double fixedDeltaTime);

    inline const std::string& GetName() const;

    template<ComponentType T, typename... Args>
    T* AddComponent(Args&&... args);

    template<ComponentType T>
    T* GetComponent();

    template<ComponentType T>
    void RemoveComponent();

    template<ComponentType T>
    bool HasComponent();

private:
    std::unordered_map<std::type_index, std::unique_ptr<Component>> m_Components{};
    std::vector<std::unique_ptr<GameObject>> m_Children{};
    std::string m_Name;
};

#pragma region Template Implementations
template<ComponentType T, typename... Args>
T* GameObject::AddComponent(Args&&... args)
{
    auto index = std::type_index(typeid(T));
    std::unique_ptr<T> component = std::make_unique<T>(std::forward<Args>(args)...);
    m_Components.emplace(index, std::move(component));
    return reinterpret_cast<T*>(m_Components[index].get());
}

template<ComponentType T>
T* GameObject::GetComponent()
{
    auto index = std::type_index(typeid(T));
    if (m_Components.find(index) != m_Components.end())
    {
        return reinterpret_cast<T*>(m_Components[index].get());
    }
    return nullptr;
}

template<ComponentType T>
void GameObject::RemoveComponent()
{
    auto index = std::type_index(typeid(T));
    if (m_Components.find(index) != m_Components.end())
    {
        m_Components.erase(index);
    }
}

template<ComponentType T>
bool GameObject::HasComponent()
{
    auto index = std::type_index(typeid(T));
    return m_Components.find(index) != m_Components.end();
}
#pragma endregion

#endif // !GAMEOBJECT_H