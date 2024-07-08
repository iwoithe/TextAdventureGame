declare_module(items)
set(MODULE_SRC
    appleitem.cpp
    appleitem.h
    iitem.h
    items.cpp
    items.h
    stubitem.cpp
    stubitem.h
)

set(MODULE_LINK
    dispatcher
    singleton
)

setup_module()
