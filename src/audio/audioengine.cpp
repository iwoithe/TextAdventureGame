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
    ma_sound_stop(&m_winSound);

    ma_sound_uninit(&m_introSound);
    ma_sound_uninit(&m_gameLoopSound);
    ma_sound_uninit(&m_winSound);
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

    result = ma_sound_init_from_file(&m_engine, String("../share/music/win.wav").cStr(), 0, NULL, NULL, &m_winSound);
    if (result != MA_SUCCESS) {
        ma_engine_uninit(&m_engine);
        throw std::runtime_error("[CRITICAL ERROR] File could not be found");
    }
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
void AudioEngine::playWin()
{
    if (!ma_sound_is_playing(&m_winSound)) {
        if (ma_sound_is_playing(&m_introSound)) {
            m_waitingForIntro = true;
        }

        if (ma_sound_is_playing(&m_gameLoopSound)) {
            ma_sound_set_looping(&m_gameLoopSound, false);
            m_waitingForGameLoop = true;
        }
    }

    while (true) {
        if (m_waitingForIntro) {
            if (ma_sound_is_playing(&m_introSound) == MA_FALSE) {
                m_waitingForIntro = false;
                m_isWinPlaying = true;
                ma_sound_start(&m_winSound);
                break;
            }
        }

        if (m_waitingForGameLoop) {
            if (ma_sound_is_playing(&m_gameLoopSound) == MA_FALSE) {
                m_waitingForGameLoop = false;
                m_gameLoopPlaying = false;
                m_isWinPlaying = true;
                ma_sound_start(&m_winSound);
                break;
            }
        }
    }

    while (m_isWinPlaying) {
        m_isWinPlaying = (bool)ma_sound_is_playing(&m_winSound);
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
    ma_sound_seek_to_pcm_frame(&m_winSound, 0);

    ma_sound_set_fade_in_milliseconds(&m_introSound, -1, 1, 0);
    ma_sound_set_fade_in_milliseconds(&m_gameLoopSound, -1, 1, 0);

    ma_sound_set_looping(&m_gameLoopSound, true);

    m_gameLoopPlaying = false;
    m_isWinPlaying = false;
    m_fadingOutIntro = false;
    m_fadingOutGameLoop = false;
    m_waitingForIntro = false;
    m_waitingForGameLoop = false;
}
