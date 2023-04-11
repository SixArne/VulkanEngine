#include "AudioSystem.h"
#include <FMOD/fmod.hpp>
#include "core/logger/log.h"

void AudioSystem::Initialize(int channels)
{
    if (!m_IsInitialized)
    {
        FMOD_RESULT result = FMOD::System_Create(&m_pSystem);
        if (result != FMOD_OK)
        {
            F_LOG_CORE_ERROR("Failed to create FMOD system");
            return;
        }

        result = m_pSystem->setOutput(FMOD_OUTPUTTYPE_AUTODETECT);
        if (result != FMOD_OK)
        {
            F_LOG_CORE_ERROR("Failed to set FMOD output");
            return;
        }

        result = m_pSystem->init(channels, FMOD_INIT_NORMAL, nullptr);
        if (result != FMOD_OK)
        {
            F_LOG_CORE_ERROR("Failed to initialize FMOD system");
            return;
        }

        m_IsInitialized = true;
    }
}

FMOD::System* AudioSystem::GetSystem() const
{
    if (!m_IsInitialized)
    {
        F_LOG_CORE_ERROR("AudioSystem is not initialized");
        return nullptr;
    }

    return m_pSystem;
}

void AudioSystem::Unload()
{
    if (m_IsInitialized)
    {
        m_pSystem->release();
        m_IsInitialized = false;
    }
}