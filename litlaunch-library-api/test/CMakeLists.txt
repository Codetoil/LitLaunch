cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(litlaunch-library-api-tests VERSION 0.1.1.2 LANGUAGES C)
set(CMAKE_C_STANDARD 90)


find_library(LITLAUNCH_LIBRARY_API
        NAMES litlaunch-library-api-0.2.4+build.1
        PATHS $ENV{BUILD_LOC}/litlaunch-library-api)

if (NOT LITLAUNCH_LIBRARY_API)
    message(NOTICE "Can't add test suite for LitLaunch Library API.")
    message(NOTICE "Please build a copy of the LitLaunch Library API, then try again.")
else ()
    add_executable(litlaunch-library-api-tests src/main/c/run.c)
    target_include_directories(litlaunch-library-api-tests PUBLIC ../src/main/public)
    target_include_directories(litlaunch-library-api-tests PRIVATE include)
    target_link_libraries(litlaunch-library-api-tests LINK_PUBLIC ${LITLAUNCH_LIBRARY_API})
    set_target_properties(
            litlaunch-library-api-tests
            PROPERTIES
            OUTPUT_NAME "litlaunch-library-api-tests-0.1.1+build.2"
    )
    add_custom_command(TARGET litlaunch-library-api-tests POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy
            "$<TARGET_FILE:litlaunch-library-api-tests>"
            "${PROJECT_SOURCE_DIR}/../builds/$<TARGET_FILE_NAME:litlaunch-library-api-tests>"
            COMMENT "Copying to output directory")
endif ()
