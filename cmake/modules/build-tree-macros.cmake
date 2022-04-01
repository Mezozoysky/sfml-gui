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

macro(init_output_directories)
    cmake_parse_arguments(ARGS # prefix
        "NO_GNU_DIRS" # list of options (boolean args)
        "OUTPUT_PREFIX" # list of single value args
        "" # list of multi value args
        ${ARGN}
        )

    set(output_dir_prefix "${CMAKE_BINARY_DIR}")
    if(ARGS_OUTPUT_PREFIX)
        set(output_dir_prefix "${ARGS_OUTPUT_PREFIX}")
    endif()

    set(bt_list ${CMAKE_CONFIGURATION_TYPES})
    if (NOT bt_list)
      set(bt_list "${CMAKE_BUILD_TYPE};")
    endif()
    foreach(bt ${bt_list})
        set(bt_upper)
        string(TOUPPER ${bt} bt_upper)
        set(archive_var_name "CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${bt_upper}")
        set(library_var_name "CMAKE_LIBRARY_OUTPUT_DIRECTORY_${bt_upper}")
        set(runtime_var_name "CMAKE_RUNTIME_OUTPUT_DIRECTORY_${bt_upper}")
        if(NOT ${archive_var_name} AND NOT ${library_var_name} AND NOT ${runtime_var_name})
            set(archive_dir "${output_dir_prefix}")
            set(library_dir "${output_dir_prefix}")
            set(runtime_dir "${output_dir_prefix}")
            if (GENERATOR_IS_MULTI_CONFIG)
                set(archive_dir "${archive_dir}/${bt}")
                set(library_dir "${library_dir}/${bt}")
                set(runtime_dir "${runtime_dir}/${bt}")
            endif()
            if(NOT ARGS_NO_GNU_DIRS)
                set(archive_dir "${archive_dir}/${CMAKE_INSTALL_LIBDIR}")
                set(library_dir "${library_dir}/${CMAKE_INSTALL_LIBDIR}")
                set(runtime_dir "${runtime_dir}/${CMAKE_INSTALL_BINDIR}")
            endif()
            set(${archive_var_name} "${archive_dir}" CACHE PATH "Output directory for static libraries." FORCE)
            set(${library_var_name} "${library_dir}" CACHE PATH "Output directory for shared libraries." FORCE)
            set(${runtime_var_name} "${runtime_dir}" CACHE PATH "Output directory for executables and DLL's." FORCE)
        endif()
        message(STATUS "${bt} archive output dir: \"${archive_dir}\"")
        message(STATUS "${bt} library output dir: \"${library_dir}\"")
        message(STATUS "${bt} runtime output dir: \"${runtime_dir}\"")
    endforeach()

endmacro()
