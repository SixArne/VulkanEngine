#include <vld.h>
#include <iostream>
#include "core/logger/Log.h"
#include "window/Window.h"
#include "core/scene/SceneManager.h"
#include "core/scene/Scene.h"
#include "ecs/components/AudioSource.h"
#include "core/systems/AudioSystem.h"

void CreateScene()
{
    Scene* scene = SceneManager::GetInstance().CreateScene();

    std::unique_ptr<GameObject> audioplayer = std::make_unique<GameObject>("AudioPlayer");
    AudioSource* source = audioplayer->AddComponent<AudioSource>();
    source->SetAudioClip("resources/sound/bluesky.mp3");

    scene->AddGameObject(std::move(audioplayer));

    SceneManager::GetInstance().SetCurrentScene(scene);
}

int main()
{
    // Initialize logger
    Log::Init();

    // Setup audio with 32 channels
    AudioSystem::GetInstance().Initialize(32);

    // Create scene
    CreateScene();

    // Create window info
    WindowCreateInfo info{};
    info.width = 1920;
    info.height = 1080;
    info.api = GraphicsAPI::OpenGL;
    info.title = "Engine";

    // Create window
    std::unique_ptr<Window> window = std::make_unique<Window>(info);

    // Run App
    window->Run();
}