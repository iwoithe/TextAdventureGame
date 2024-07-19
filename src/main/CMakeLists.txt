add_executable(textadventuregame)

target_sources(textadventuregame PRIVATE main.cpp)
target_include_directories(textadventuregame PUBLIC
    ${GLOBAL_INCLUDE}
)
target_link_libraries(textadventuregame PRIVATE
    ${GLOBAL_LIBRARIES}
    singleton
    game
)

if (MSVC)
    set_property(TARGET textadventuregame PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT textadventuregame)
endif()

install(TARGETS textadventuregame DESTINATION bin)
