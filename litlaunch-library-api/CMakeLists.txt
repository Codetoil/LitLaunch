cmake_minimum_required(VERSION 3.10)
project(litlaunch-library-api VERSION 0.2.1.2 LANGUAGES C)

set(CMAKE_C_STANDARD 90)

add_library(litlaunch-library-api STATIC src/main/c/litlaunch-library-api.c)

target_include_directories(litlaunch-library-api PUBLIC include src/main/public)

if(EXISTS $ENV{BUILD_LOC}/litlaunch-library-api/liblitlaunch-library-api.a)
add_subdirectory(test)
endif()