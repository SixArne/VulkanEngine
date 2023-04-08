#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <unordered_map>
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

private:
    std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components;
};


template<ComponentType T>
T* GameObject::AddComponent()
{
    auto index = std::type_index(typeid(T));
    std::unique_ptr<T> component = std::make_unique<T>();
    m_components.emplace(index, std::move(component));
    return reinterpret_cast<T*>(m_components[index].get());
}

#endif // !GAMEOBJECT_H