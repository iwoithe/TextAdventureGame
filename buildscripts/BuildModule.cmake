set(GLOBAL_INCLUDE
    ${PROJECT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/thirdparty
    ${PROJECT_SOURCE_DIR}/thirdparty/iwstring
)

set(GLOBAL_LIBRARIES
    iwstring
)

macro(declare_module name)
    set(MODULE ${name})
    unset(MODULE_INCLUDE)
    unset(MODULE_SRC)
    unset(MODULE_LINK)
endmacro()

macro(setup_module)
    add_library(${MODULE})
    target_sources(${MODULE} PRIVATE ${MODULE_SRC})
    target_include_directories(${MODULE} PUBLIC
        ${GLOBAL_INCLUDE}
        ${MODULE_INCLUDE}
    )

    target_link_libraries(${MODULE} PRIVATE
        ${GLOBAL_LIBRARIES}
        ${MODULE_LINK}
    )
endmacro()
