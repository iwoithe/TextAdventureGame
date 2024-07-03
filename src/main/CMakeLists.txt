add_executable(textadventure)

target_sources(textadventure PRIVATE main.cpp)
target_include_directories(textadventure PUBLIC
    ${GLOBAL_INCLUDE}
)
target_link_libraries(textadventure PRIVATE
    ${GLOBAL_LIBRARIES}
)
