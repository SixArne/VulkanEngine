#ifndef AUDIO_SOURCE_H
#define AUDIO_SOURCE_H

#include <FMOD/fmod.hpp>
#include <thread>
#include <atomic>

#include "ecs/Component.h"
#include "ecs/GameObject.h"

class AudioSource final : public Component
{
public:
    AudioSource() {};
    AudioSource(GameObject* pOwner);
    ~AudioSource();

    void Init() override;
    void Shutdown() override;
    void Update(double deltaTime) override;
    void FixedUpdate(double fixedDeltaTime) override;
    void RenderImGui() override;
    void LateUpdate(double fixedDeltaTime) override;

    void SetAudioClip(const std::string& path);
    void Play();
    void Pause();

private:
    void AudioThread();

    FMOD::Channel* m_pChannel;
    FMOD::Sound* m_pSound;

    std::thread m_AudioThread;
    float m_Volume{0.5f};

    std::atomic<bool> m_UseAutoPlay{true};
    std::atomic<bool> m_IsPlaying{false};

    bool m_IsShutDown{false};
};

#endif // AUDIO_SOURCE_H