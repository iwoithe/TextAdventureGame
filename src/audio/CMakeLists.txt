declare_module(audio)
set(MODULE_SRC
    audioengine.cpp
    audioengine.h
)

set(MODULE_LINK
    miniaudio
)

setup_module()
