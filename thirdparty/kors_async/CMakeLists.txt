include(${CMAKE_CURRENT_LIST_DIR}/async/async.cmake)

declare_module(kors_async)
set(MODULE_SRC ${KORS_ASYNC_SRC})
set(MODULE_USE_GLOBAL OFF)

setup_module()
