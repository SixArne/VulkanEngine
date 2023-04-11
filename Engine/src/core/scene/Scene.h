#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>

#include "ecs/GameObject.h"

class Scene
{
public:
    Scene(const std::string& name);
    ~Scene();

    void Init();
    void Shutdown();
    void Update(double deltaTime);
    void FixedUpdate(double fixedDeltaTime);
    void RenderImGui();
    void LateUpdate(double fixedDeltaTime);

    const std::string& GetName() const { return m_Name; }

    void AddGameObject(std::unique_ptr<GameObject> gameObject);

private:
    std::string m_Name;
    std::vector<std::unique_ptr<GameObject>> m_GameObjects;
};

#endif // SCENE_H
