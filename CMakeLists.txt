cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

cmake_policy(SET CMP0028 NEW)

set(sfml_gui_VERSION_MAJOR 0)
set(sfml_gui_VERSION_MINOR 1)
set(sfml_gui_VERSION_PATCH 0)
set(sfml_gui_VERSION "${sfml_gui_VERSION_MAJOR}.${sfml_gui_VERSION_MINOR}.${sfml_gui_VERSION_PATCH}")

message(STATUS "CMake source directory: ${CMAKE_SOURCE_DIR}")
message(STATUS "sfml-gui source directory: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMake build directory: ${CMAKE_BINARY_DIR}")
message(STATUS "sfml-gui build directory: ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "sfml_gui version: ${sfml_gui_VERSION}")

project(sfml-gui
    VERSION ${sfml_gui_VERSION}
    LANGUAGES CXX)

list(PREPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/modules")

option(sfml_gui_BUILD_SHARED_LIBS "Compile sfml-gui as dynamic library" ${BUILD_SHARED_LIBS})
option(sfml_gui_BUILD_DEMO "Build sfml-gui demo app" ON)

set(sfml_gui_GEN_SRC_PATH "${CMAKE_CURRENT_BINARY_DIR}/gensrc")
message(STATUS "sfml-gui generated sources directory: ${sfml_gui_GEN_SRC_PATH}")

include(GNUInstallDirs)

find_package(SFML 2.5 CONFIG REQUIRED
    COMPONENTS system window graphics
    )

set(sfml_gui_EXPORT_NAME "sfml_gui_targets")
add_subdirectory(libsfml-gui)
if (sfml_gui_BUILD_DEMO)
    add_subdirectory(demo)
endif(sfml_gui_BUILD_DEMO)

# Handle cmake config
include(CMakePackageConfigHelpers)
set(sfml_gui_TARGETS_FILENAME sfml-gui-targets.cmake)
set(sfml_gui_VERSION_CONFIG ${PROJECT_BINARY_DIR}/sfml-gui-config-version.cmake)
set(sfml_gui_PROJECT_CONFIG ${PROJECT_BINARY_DIR}/sfml-gui-config.cmake)
set(sfml_gui_TARGETS_CONFIG ${PROJECT_BINARY_DIR}/${sfml_gui_TARGETS_FILENAME})
set(sfml_gui_CONFIG_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/${CMAKE_PROJECT_NAME}/)
# create cmake config
write_basic_package_version_file(${sfml_gui_VERSION_CONFIG}
                                 VERSION ${sfml_gui_VERSION}
                                 COMPATIBILITY AnyNewerVersion
                                 )
configure_package_config_file(${PROJECT_SOURCE_DIR}/cmake/sfml-gui-config.cmake.in
                              ${sfml_gui_PROJECT_CONFIG}
                              INSTALL_DESTINATION ${sfml_gui_CONFIG_INSTALL_DIR}
                              )
export(EXPORT ${sfml_gui_EXPORT_NAME}
    FILE ${sfml_gui_TARGETS_CONFIG}
    NAMESPACE sfml-gui::
    )
install(FILES ${sfml_gui_PROJECT_CONFIG} ${sfml_gui_VERSION_CONFIG}
    DESTINATION ${sfml_gui_CONFIG_INSTALL_DIR}
    )
install(EXPORT ${sfml_gui_EXPORT_NAME}
    FILE ${sfml_gui_TARGETS_FILENAME}
    DESTINATION ${sfml_gui_CONFIG_INSTALL_DIR}
    NAMESPACE sfml-gui::
    )

###
# Install misc files
###
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${CMAKE_PROJECT_NAME}/
        )
install(FILES README.md LICENSE.md
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${CMAKE_PROJECT_NAME}/
        )
