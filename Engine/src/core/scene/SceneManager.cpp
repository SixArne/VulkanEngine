#include "SceneManager.h"
#include "Scene.h"

void SceneManager::Init()
{
    m_CurrentScene->Init();
}

void SceneManager::Shutdown()
{
    m_CurrentScene->Shutdown();
}

void SceneManager::Update(double deltaTime)
{
    m_CurrentScene->Update(deltaTime);
}

void SceneManager::FixedUpdate(double fixedDeltaTime)
{
    m_CurrentScene->FixedUpdate(fixedDeltaTime);
}

void SceneManager::RenderImGui()
{
    m_CurrentScene->RenderImGui();
}

void SceneManager::LateUpdate(double fixedDeltaTime)
{
    m_CurrentScene->LateUpdate(fixedDeltaTime);
}

Scene* SceneManager::CreateScene()
{
    m_Scenes.emplace_back(std::make_unique<Scene>("Scene"));
    return m_Scenes.back().get();
}

void SceneManager::SetCurrentScene(Scene* scene)
{
    m_CurrentScene = scene;
}
