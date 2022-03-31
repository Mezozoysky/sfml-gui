cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(sfml-gui-lib
    VERSION ${sfml_gui_VERSION}
    LANGUAGES CXX)

add_library(${PROJECT_NAME})
add_library(sfml-gui::sfml-gui ALIAS ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME}
    PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED TRUE
    OUTPUT_NAME sfml-gui
    )

target_link_libraries(${PROJECT_NAME}
    INTERFACE
    sfml-graphics
    sfml-window
    sfml-system
    )
target_include_directories(${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    $<TARGET_PROPERTY:sfml-system,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:sfml-window,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:sfml-graphics,INTERFACE_INCLUDE_DIRECTORIES>
    )


install (TARGETS ${PROJECT_NAME}
    EXPORT ${sfml_gui_EXPORT_NAME}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/sfml-gui"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.hpp"
    )


set(HEADER_FILES
    sfml-gui/gui.hpp
    sfml-gui/text.hpp
    sfml-gui/checkbox.hpp
    sfml-gui/slider.hpp
    sfml-gui/button.hpp
    sfml-gui/listbox.hpp
    )

set(SOURCE_FILES
    sfml-gui/gui.cpp
    sfml-gui/text.cpp
    sfml-gui/checkbox.cpp
    sfml-gui/slider.cpp
    sfml-gui/button.cpp
    sfml-gui/listbox.cpp
    )

source_group(TREE ${CMAKE_CURRENT_LIST_DIR}
    # PREFIX PTTT\\${PROJECT_NAME}
    FILES ${HEADER_FILES} ${SOURCE_FILES}
    )

target_sources(${PROJECT_NAME}
    PRIVATE ${SOURCE_FILES}
    )
