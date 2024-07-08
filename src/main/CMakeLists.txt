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
