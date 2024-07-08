declare_module(player)
set(MODULE_SRC
    player.cpp
    player.h
)

set(MODULE_LINK
    dispatcher
    items
)

setup_module()
