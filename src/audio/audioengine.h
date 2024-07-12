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

    void initSounds();

    void start();
    void processEvents();

    void playWin();

    void fadeOutAudio();

    void reset();

private:
    ma_engine m_engine;

    ma_sound m_introSound;
    ma_sound m_gameLoopSound;
    ma_sound m_winSound;

    bool m_gameLoopPlaying = false;
    bool m_isWinPlaying = false;

    bool m_waitingForIntro = false;
    bool m_waitingForGameLoop = false;

    bool m_fadingOutIntro = false;
    bool m_fadingOutGameLoop = false;
};

#endif // AUDIO_AUDIOENGINE_H
