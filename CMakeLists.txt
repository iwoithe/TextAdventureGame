cmake_minimum_required(VERSION 3.20)
project(TextAdventureGame LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${PROJECT_SOURCE_DIR}/buildscripts/BuildModule.cmake)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_INSTALL_PREFIX ./install)

add_subdirectory(thirdparty)
add_subdirectory(src)

install(DIRECTORY share DESTINATION .)
