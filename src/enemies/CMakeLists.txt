declare_module(enemies)
set(MODULE_SRC
    enemies.cpp
    enemies.h
    enemymanager.cpp
    enemymanager.h
    goblin.cpp
    goblin.h
    ienemy.h
)

set(MODULE_LINK
    dispatcher
    singleton
)

setup_module()
