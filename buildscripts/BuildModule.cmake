set(GLOBAL_INCLUDE
    ${PROJECT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/thirdparty
    ${PROJECT_SOURCE_DIR}/thirdparty/iwany
    ${PROJECT_SOURCE_DIR}/thirdparty/iwstring
    ${PROJECT_SOURCE_DIR}/thirdparty/iwvariant
    ${PROJECT_SOURCE_DIR}/thirdparty/kors_async/include
)

set(GLOBAL_LIBRARIES
    global
    iwany
    iwstring
    iwvariant
    kors_async
)

macro(declare_module name)
    set(MODULE ${name})
    unset(MODULE_INCLUDE)
    unset(MODULE_SRC)
    unset(MODULE_LINK)
    # Include and link GLOBAL_INCLUDE and GLOBAL_LIBRARIES respectively
    set(MODULE_USE_GLOBAL ON)
endmacro()

macro(setup_module)
    add_library(${MODULE})

    target_sources(${MODULE} PRIVATE ${MODULE_SRC})

    target_include_directories(${MODULE} PUBLIC ${MODULE_INCLUDE})

    if (${MODULE_USE_GLOBAL})
        target_include_directories(${MODULE} PUBLIC ${GLOBAL_INCLUDE})
    endif()

    target_link_libraries(${MODULE} PRIVATE ${MODULE_LINK})

    if (${MODULE_USE_GLOBAL})
        target_link_libraries(${MODULE} PRIVATE ${GLOBAL_LIBRARIES})
    endif()
endmacro()
