declare_module(game)
set(MODULE_SRC
    game.cpp
    game.h
)

set(MODULE_LINK
    dispatcher
    items
    player
    room
    singleton
    spells
)

setup_module()
