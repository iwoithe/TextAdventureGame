declare_module(singleton)
set(MODULE_SRC
    singletonmanager.cpp
    singletonmanager.h
)

set(MODULE_LINK
    audio
    dispatcher
)

setup_module()
