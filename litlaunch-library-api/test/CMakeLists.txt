cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
set(CMAKE_C_STANDARD 90)


find_library(LITLAUNCH_LIBRARY_API
        NAMES litlaunch-library-api-0.2.3+build.0
        PATHS $ENV{BUILD_LOC}/litlaunch-library-api)

if (NOT LITLAUNCH_LIBRARY_API)
    message(NOTICE "Can't add test suite for LitLaunch Library API.")
    message(NOTICE "Please build a copy of the LitLaunch Library API, then try again.")
else ()
    add_executable(litlaunch-library-api-test1 src/main/c/run.c)
    target_include_directories(litlaunch-library-api-test1 PUBLIC ../src/main/public)
    target_include_directories(litlaunch-library-api-test1 PUBLIC include)
    target_link_libraries(litlaunch-library-api-test1 LINK_PUBLIC ${LITLAUNCH_LIBRARY_API})
endif ()
