declare_module(spells)
set(MODULE_SRC
    ispell.cpp
    ispell.h
    killspell.cpp
    killspell.h
    spells.cpp
    spells.h
)

set(MODULE_LINK
    dispatcher
    singleton
)

setup_module()
