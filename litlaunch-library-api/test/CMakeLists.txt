cmake_minimum_required(VERSION 3.14.0 FATAL_ERROR)
set(CMAKE_C_STANDARD 90)

add_executable(litlaunch-library-api-exe-test1 src/main/c/run.c)

find_library(LITLAUNCH_LIBRARY_API litlaunch-library-api $ENV{BUILD_LOC}/litlaunch-library-api)

target_include_directories(litlaunch-library-api-exe-test1 PUBLIC ../src/main/public)
target_include_directories(litlaunch-library-api-exe-test1 PUBLIC include)
target_link_libraries(litlaunch-library-api-exe-test1 LINK_PUBLIC ${LITLAUNCH_LIBRARY_API})