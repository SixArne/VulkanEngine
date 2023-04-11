#include "AudioSource.h"
#include "core/systems/AudioSystem.h"
#include "core/logger/Log.h"

AudioSource::AudioSource(GameObject* pOwner)
    : Component(pOwner)
{
}

AudioSource::~AudioSource()
{
    if (!m_IsShutDown)
    {
        Shutdown();
    }
}

void AudioSource::SetAudioClip(const std::string& path)
{
    auto system = AudioSystem::GetInstance().GetSystem();
    FMOD_RESULT result = system->createStream(path.c_str(), FMOD_DEFAULT | FMOD_CREATESTREAM, nullptr, &m_pSound);
    if (result != FMOD_OK) {
        F_LOG_CORE_ERROR("Failed to load sound file: {0}", path);
        return;
    }
}

void AudioSource::Play()
{
    auto system = AudioSystem::GetInstance().GetSystem();
    FMOD_RESULT result = system->playSound(m_pSound, nullptr, false, &m_pChannel);
    if (result != FMOD_OK) {
        F_LOG_CORE_ERROR("Failed to play sound");
        return;
    }

    m_IsPlaying = true;

    m_AudioThread = std::thread(&AudioSource::AudioThread, this);
}

void AudioSource::Pause()
{
    if (m_IsPlaying)
    {
        m_pChannel->setPaused(true);
        m_IsPlaying = false;
    }
}

void AudioSource::AudioThread()
{
    bool isPlaying = true;
    while (isPlaying && m_IsPlaying)
    {
        m_pChannel->isPlaying(&isPlaying);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void AudioSource::Init()
{
    Play();
}

void AudioSource::Shutdown()
{
    m_AudioThread.join();
    m_pSound->release();
    m_pChannel->stop();
}

void AudioSource::Update(double deltaTime)
{
}

void AudioSource::FixedUpdate(double fixedDeltaTime)
{
}

void AudioSource::RenderImGui()
{
}

void AudioSource::LateUpdate(double fixedDeltaTime)
{
}
