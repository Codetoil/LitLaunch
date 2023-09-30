cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 98)

add_library(litlaunch_library_api STATIC src/main/c/litlaunch-library-api.c)

target_include_directories(litlaunch_library_api PUBLIC include src/main/public)

if(EXISTS ../build/litlaunch-library-api/liblitlaunch_library_api.a)
add_subdirectory(test)
endif()