#include <vld.h>
#include <iostream>
#include "core/logger/Log.h"
#include "window/Window.h"
#include <FMOD/fmod.hpp>

#include <FMOD/fmod.hpp>
#include <thread>

void playSound(FMOD::System* system, const char* soundFile) {
    // Load the sound file as a stream
    FMOD::Sound* sound;
    FMOD_RESULT result = system->createStream(soundFile, FMOD_DEFAULT | FMOD_CREATESTREAM, nullptr, &sound);
    if (result != FMOD_OK) {
        // Handle error
        return;
    }

    // Play the sound
    FMOD::Channel* channel;
    result = system->playSound(sound, nullptr, false, &channel);
    if (result != FMOD_OK) {
        // Handle error
        return;
    }

    channel->setVolume(0.2f);

    // Wait for the sound to finish playing
    bool isPlaying = true;
    while (isPlaying) {
        result = channel->isPlaying(&isPlaying);
        if (result != FMOD_OK) {
            // Handle error
            return;
        }
        // Sleep for a short time to avoid hogging the CPU
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    // Release the sound
    sound->release();
}

int main()
{
    // Initialize logger
    Log::Init();

    // Initialize the FMOD system
    FMOD::System* system;
    FMOD_RESULT result = FMOD::System_Create(&system);
    if (result != FMOD_OK) {
        // Handle error
        F_LOG_CORE_ERROR("Failed to create FMOD system");
        return 1;
    }
    result = system->setOutput(FMOD_OUTPUTTYPE_AUTODETECT);
    if (result != FMOD_OK) {
        // Handle error
        F_LOG_CORE_ERROR("Failed to set FMOD output");
        return 1;
    }
    result = system->init(32, FMOD_INIT_NORMAL, nullptr);
    if (result != FMOD_OK) {
        // Handle error
        F_LOG_CORE_ERROR("Failed to initialize FMOD system");
        return 1;
    }

    // Start playing the sound on a separate thread
    std::thread soundThread(playSound, system, "resources/sound/levelComplete.mp3");



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

    // Wait for the sound to finish playing
    soundThread.join();

    // Release the FMOD system
    system->release();

    // Do some other work while the sound is playing
}