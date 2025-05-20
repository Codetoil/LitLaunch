cmake_minimum_required(VERSION 3.15)
project(litlaunch-library-api VERSION 0.2.3.1 LANGUAGES C)

set(CMAKE_C_STANDARD 90)

add_library(litlaunch-library-api STATIC src/main/c/litlaunch-library-api.c
        src/main/c/location.c
        src/main/c/dependencies.c
        src/main/c/simple_string_lib.h
        src/main/public/litlaunch/location.h
        src/main/public/litlaunch/dependencies.h
        src/main/public/litlaunch/litlaunch-library-api.h
)
set_target_properties(
        litlaunch-library-api
        PROPERTIES
            OUTPUT_NAME "litlaunch-library-api-0.2.3+build.1"
)

target_include_directories(litlaunch-library-api PUBLIC include src/main/public)

add_custom_command(TARGET litlaunch-library-api POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy
        "$<TARGET_FILE:litlaunch-library-api>"
        "${PROJECT_SOURCE_DIR}/builds/$<TARGET_FILE_NAME:litlaunch-library-api>"
        COMMENT "Copying to output directory")

add_subdirectory(test)