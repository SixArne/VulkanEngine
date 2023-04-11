#ifndef SCENE_MANAGHER_H
#define SCENE_MANAGHER_H

#include <vector>
#include <memory>
#include "core/Singleton.h"
#include "core/scene/Scene.h"

class Scene;

class SceneManager final : public Singleton<SceneManager>
{
public:
    void Init();
    void Shutdown();
    void Update(double deltaTime);
    void FixedUpdate(double fixedDeltaTime);
    void RenderImGui();
    void LateUpdate(double fixedDeltaTime);

    Scene* CreateScene();
    void SetCurrentScene(Scene* scene);

private:
    friend class Singleton<SceneManager>;
    SceneManager() = default;

    Scene* m_CurrentScene;
    std::vector<std::unique_ptr<Scene>> m_Scenes{};
};

#endif // SCENE_MANAGHER_H
