#include "audioengine.h"

#include <stdexcept>

AudioEngine::AudioEngine()
{
    initEngine();
}

AudioEngine::~AudioEngine()
{
    deInitEngine();
}

void AudioEngine::initEngine()
{
    ma_result result;
    result = ma_engine_init(NULL, &m_engine);
    if (result != MA_SUCCESS) {
        throw std::runtime_error("[CRITICAL ERROR] Audio engine failed to initialize");
    }
}

void AudioEngine::deInitEngine()
{
    ma_engine_uninit(&m_engine);
}
