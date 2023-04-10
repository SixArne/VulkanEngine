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
    GameObject() = default;
    ~GameObject() = default;

    template<ComponentType T>
    T* AddComponent();

    template<ComponentType T>
    T* GetComponent();

    template<ComponentType T>
    void RemoveComponent();

    template<ComponentType T>
    bool HasComponent();

private:
    std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components{};
    std::vector<std::unique_ptr<GameObject>> m_Children{};
};

#pragma region Template Implementations
template<ComponentType T>
T* GameObject::AddComponent()
{
    auto index = std::type_index(typeid(T));
    std::unique_ptr<T> component = std::make_unique<T>();
    m_components.emplace(index, std::move(component));
    return reinterpret_cast<T*>(m_components[index].get());
}

template<ComponentType T>
T* GameObject::GetComponent()
{
    auto index = std::type_index(typeid(T));
    if (m_components.find(index) != m_components.end())
    {
        return reinterpret_cast<T*>(m_components[index].get());
    }
    return nullptr;
}

template<ComponentType T>
void GameObject::RemoveComponent()
{
    auto index = std::type_index(typeid(T));
    if (m_components.find(index) != m_components.end())
    {
        m_components.erase(index);
    }
}

template<ComponentType T>
bool GameObject::HasComponent()
{
    auto index = std::type_index(typeid(T));
    return m_components.find(index) != m_components.end();
}
#pragma endregion

#endif // !GAMEOBJECT_H