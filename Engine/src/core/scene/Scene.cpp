#include "Scene.h"

Scene::Scene(const std::string& name)
    : m_Name(name)
{
}

Scene::~Scene()
{
}

void Scene::Init()
{
    for (const auto& obj: m_GameObjects)
        obj->Init();
}

void Scene::AddGameObject(std::unique_ptr<GameObject> gameObject)
{
    m_GameObjects.emplace_back(std::move(gameObject));
}

void Scene::Shutdown()
{
}

void Scene::Update(double deltaTime)
{
}

void Scene::FixedUpdate(double fixedDeltaTime)
{
}

void Scene::RenderImGui()
{
}

void Scene::LateUpdate(double fixedDeltaTime)
{
}