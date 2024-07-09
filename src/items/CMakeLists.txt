declare_module(items)
set(MODULE_SRC
    appleitem.cpp
    appleitem.h
    breaditem.cpp
    breaditem.h
    iitem.h
    items.cpp
    items.h
    lavabucketitem.cpp
    lavabucketitem.h
    spellpotionitem.cpp
    spellpotionitem.h
    stubitem.cpp
    stubitem.h
)

set(MODULE_LINK
    dispatcher
    singleton
)

setup_module()
