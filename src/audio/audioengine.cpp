#include "audioengine.h"

#include <stdexcept>

AudioEngine::AudioEngine()
{
    initAudioEngine();
    initSounds();
}

AudioEngine::~AudioEngine()
{
    deInitAudioEngine();
}

void AudioEngine::initAudioEngine()
{
    ma_result result = ma_engine_init(NULL, &m_engine);
    if (result != MA_SUCCESS) {
        throw std::runtime_error("[CRITICAL ERROR] Audio engine failed to initialize engine");
    }
}

void AudioEngine::deInitAudioEngine()
{
    ma_sound_stop(&m_introSound);
    ma_sound_set_looping(&m_gameLoopSound, false);
    ma_sound_stop(&m_gameLoopSound);

    ma_sound_uninit(&m_introSound);
    ma_sound_uninit(&m_gameLoopSound);
    ma_engine_uninit(&m_engine);
}

void AudioEngine::initSounds()
{
    ma_result result;
    result = ma_sound_init_from_file(&m_engine, String("../share/music/intro.wav").cStr(), 0, NULL, NULL, &m_introSound);
    if (result != MA_SUCCESS) {
        ma_engine_uninit(&m_engine);
        throw std::runtime_error("[CRITICAL ERROR] File could not be found");
    }

    result = ma_sound_init_from_file(&m_engine, String("../share/music/gameloop.wav").cStr(), 0, NULL, NULL, &m_gameLoopSound);
    if (result != MA_SUCCESS) {
        ma_engine_uninit(&m_engine);
        throw std::runtime_error("[CRITICAL ERROR] File could not be found");
    }

    ma_sound_set_looping(&m_gameLoopSound, true);
}

void AudioEngine::start()
{
    ma_sound_start(&m_introSound);
}

void AudioEngine::processEvents()
{
    if (!ma_sound_is_playing(&m_introSound) && !m_gameLoopPlaying) {
        m_gameLoopPlaying = true;
        ma_sound_start(&m_gameLoopSound);
    }
}

void AudioEngine::fadeOutAudio()
{
    if (!m_gameLoopPlaying) {
        m_fadingOutIntro = true;
        ma_sound_set_fade_in_milliseconds(&m_introSound, -1, 0, 1000);
    }

    if (m_gameLoopPlaying) {
        m_fadingOutGameLoop = true;
        ma_sound_set_looping(&m_gameLoopSound, false);
        ma_sound_set_fade_in_milliseconds(&m_gameLoopSound, -1, 0.0f, 1000);
    }

    if (m_fadingOutIntro) {
        while (true) {
            if (!ma_sound_is_playing(&m_introSound) || ma_sound_get_current_fade_volume(&m_introSound) <= 0.0f) {
                break;
            }
        }

        ma_sound_stop(&m_introSound);
    }

    if (m_fadingOutGameLoop) {
        while (true) {
            if (!ma_sound_is_playing(&m_gameLoopSound) || ma_sound_get_current_fade_volume(&m_gameLoopSound) <= 0.0f) {
                break;
            }
        }

        ma_sound_stop(&m_gameLoopSound);
    }
}

void AudioEngine::reset()
{
    ma_sound_seek_to_pcm_frame(&m_introSound, 0);
    ma_sound_seek_to_pcm_frame(&m_gameLoopSound, 0);

    ma_sound_set_fade_in_milliseconds(&m_introSound, -1, 1, 1000);
    ma_sound_set_fade_in_milliseconds(&m_gameLoopSound, -1, 1, 1000);

    ma_sound_set_looping(&m_gameLoopSound, true);
}
