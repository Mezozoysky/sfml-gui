cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(demo
    LANGUAGES CXX)

add_executable(${PROJECT_NAME})
add_executable(sfml-gui::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME}
    PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED TRUE)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    sfml-gui::libsfml-gui
    sfml-graphics
    sfml-window
    sfml-system
    )
target_include_directories(${PROJECT_NAME}
    PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}")


set(SOURCE_FILES
    main.cpp
    )

source_group(TREE ${CMAKE_CURRENT_LIST_DIR}
    PREFIX pttt
    FILES ${SOURCE_FILES}
    )

target_sources(${PROJECT_NAME}
    PRIVATE ${SOURCE_FILES}
    )
