#include "audioengine.h"

#include <stdexcept>

AudioEngine::AudioEngine()
{
    initAudioEngine();
}

AudioEngine::~AudioEngine()
{
    deInitAudioEngine();
}

void AudioEngine::initAudioEngine()
{
    ma_device_config deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format = ma_format_unknown;
    deviceConfig.playback.channels = 0;
    deviceConfig.sampleRate = 0;
    // deviceConfig.dataCallback = dataCallback;
    // config.pUserData = pMyCustomData;

    if (ma_device_init(NULL, &deviceConfig, &m_device) != MA_SUCCESS) {
        throw std::runtime_error("[CRITICAL ERROR] Audio engine to initialize device");
    }

    ma_device_start(&m_device);

    if (ma_engine_init(NULL, &m_engine) != MA_SUCCESS) {
        ma_device_uninit(&m_device);
        throw std::runtime_error("[CRITICAL ERROR] Audio engine failed to initialize engine");
    }
}

void AudioEngine::deInitAudioEngine()
{
    ma_sound_uninit(&m_introSound);
    ma_engine_uninit(&m_engine);
    ma_device_uninit(&m_device);
    ma_device_uninit(&m_gameLoopDevice);
    ma_decoder_uninit(&m_gameLoopDecoder);
}

#include <iostream>

void AudioEngine::playFile(const String& filePath)
{
    // ma_result result;
    // result = ma_engine_play_sound(&m_engine, filePath.cStr(), NULL);
    // if (result != MA_SUCCESS) {
    //     throw std::runtime_error("[ERROR] Audio engine could not load file");
    // }

    ma_result result;

    result = ma_sound_init_from_file(&m_engine, filePath.cStr(), 0, NULL, NULL, &m_introSound);
    if (result != MA_SUCCESS) {
        deInitAudioEngine();
        throw std::runtime_error("[CRITICAL ERROR] File could not be found");
    }

    ma_sound_start(&m_introSound);
}

void gameLoopCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
    if (pDecoder == NULL) {
        return;
    }

    /* Reading PCM frames will loop based on what we specified when called ma_data_source_set_looping(). */
    ma_data_source_read_pcm_frames(pDecoder, pOutput, frameCount, NULL);

    (void)pInput;
}

void AudioEngine::playFileLoop(const String& fileName)
{
    ma_result result;
    ma_device_config deviceConfig;

    result = ma_decoder_init_file(fileName.cStr(), NULL, &m_gameLoopDecoder);
    if (result != MA_SUCCESS) {
        //
    }

    ma_data_source_set_looping(&m_gameLoopDecoder, MA_TRUE);

    deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format   = m_gameLoopDecoder.outputFormat;
    deviceConfig.playback.channels = m_gameLoopDecoder.outputChannels;
    deviceConfig.sampleRate        = m_gameLoopDecoder.outputSampleRate;
    deviceConfig.dataCallback      = &gameLoopCallback;
    deviceConfig.pUserData         = &m_gameLoopDecoder;

    if (ma_device_init(NULL, &deviceConfig, &m_gameLoopDevice) != MA_SUCCESS) {
        // printf("Failed to open playback device.\n");
        ma_decoder_uninit(&m_gameLoopDecoder);
    }

    if (ma_device_start(&m_gameLoopDevice) != MA_SUCCESS) {
        // printf("Failed to start playback device.\n");
        ma_device_uninit(&m_gameLoopDevice);
        ma_decoder_uninit(&m_gameLoopDecoder);
    }
}

bool AudioEngine::isIntroDone() const
{
    return !ma_sound_is_playing(&m_introSound);
}

void AudioEngine::start()
{
    playFile("../share/music/intro.wav");
}

void AudioEngine::processEvents()
{
    if (isIntroDone() && !m_gameLoopPlaying) {
        m_gameLoopPlaying = true;
        playFileLoop("../share/music/gameloop.wav");
    }
}
