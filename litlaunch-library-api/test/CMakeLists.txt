cmake_minimum_required(VERSION 3.20)
project(litlaunch_library_api)

set(CMAKE_CXX_STANDARD 98)

add_executable(litlaunch_library_api_test test/src/main/c/run.c)

find_library(LITLAUNCH_LIBRARY_API litlaunch_library_api lib)

target_include_directories(litlaunch_library_api_test PUBLIC lib/uthash)
target_include_directories(litlaunch_library_api_test PUBLIC lib/munit)
target_link_libraries(litlaunch_library_api_test LINK_PUBLIC ${LITLAUNCH_LIBRARY_API})