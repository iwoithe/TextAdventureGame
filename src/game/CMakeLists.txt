declare_module(game)
set(MODULE_SRC
    game.cpp
    game.h
)

set(MODULE_LINK
    items
    room
)

setup_module()
