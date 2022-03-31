cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

include(CMakeParseArguments)

macro(init_build_types)
    cmake_parse_arguments(ARGS # prefix
        "" # list of booleans
        "DEFAULT" # list of single values
        "AVAILABLE" # list of multi values
        ${ARGN}
        )

    if (GENERATOR_IS_MULTI_CONFIG)
      if (NOT CMAKE_CONFIGURATION_TYPES)
          set(CMAKE_CONFIGURATION_TYPES ${ARGS_AVAILABLE})
      endif()
      message(STATUS "build configurations: ${CMAKE_CONFIGURATION_TYPES}")
    else()
        if (NOT CMAKE_BUILD_TYPE)
            set(CMAKE_BUILD_TYPE "${ARGS_DEFAULT}")
        endif()
        set(CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE}" CACHE STRING "Build type" FORCE)
        set_property(CACHE CMAKE_BUILD_TYPE
                     PROPERTY STRINGS ${ARGS_AVAILABLE})
        message(STATUS "build type: ${CMAKE_BUILD_TYPE}")
    endif()
endmacro()

