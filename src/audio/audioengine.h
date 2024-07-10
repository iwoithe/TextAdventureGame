#ifndef AUDIO_AUDIOENGINE_H
#define AUDIO_AUDIOENGINE_H

#include "miniaudio/miniaudio.h"

class AudioEngine
{
public:
    AudioEngine();
    ~AudioEngine();

    void initEngine();
    void deInitEngine();
private:
    ma_engine m_engine;
};

#endif // AUDIO_AUDIOENGINE_H
