#ifndef AUDIO_AUDIOENGINE_H
#define AUDIO_AUDIOENGINE_H

#include "miniaudio/miniaudio.h"

#include "iwstring.h"

using namespace iw;

class AudioEngine
{
public:
    AudioEngine();
    ~AudioEngine();

    void initAudioEngine();
    void deInitAudioEngine();

    void playFile(const String& filePath);
    void playFileLoop(const String& filePath);

    bool isIntroDone() const;

    void start();
    void processEvents();
private:
    ma_engine m_engine;
    ma_device m_device;

    ma_sound m_introSound;

    ma_device m_gameLoopDevice;
    ma_decoder m_gameLoopDecoder;

    bool m_gameLoopPlaying = false;
};

void gameLoopCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);

#endif // AUDIO_AUDIOENGINE_H
