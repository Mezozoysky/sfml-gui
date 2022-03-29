cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(sfml-gui
    VERSION 0.1.0
    LANGUAGES CXX)

list(PREPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/modules")

find_package(SFML 2.5 CONFIG REQUIRED
    COMPONENTS system window graphics
    )
#add_subdirectory(dependencies)
add_subdirectory(sources)

