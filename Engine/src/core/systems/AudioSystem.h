#ifndef AUDIO_SYSTEM_H
#define AUDIO_SYSTEM_H

#include <FMOD/fmod.hpp>
#include "core/Singleton.h"

class AudioSystem final : public Singleton<AudioSystem>
{
public:
    void Initialize(int channels);
    void Unload();
    FMOD::System* GetSystem() const;

private:
    friend class Singleton<AudioSystem>;
    AudioSystem() = default;
    ~AudioSystem() = default;
    bool m_IsInitialized{false};
    FMOD::System* m_pSystem;
};

#endif // AUDIO_SYSTEM_H
