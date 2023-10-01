cmake_minimum_required(VERSION 3.14.0 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 98)

add_executable(litlaunch_library_api_exe_test1 src/main/c/run.c)

find_library(LITLAUNCH_LIBRARY_API litlaunch_library_api ../../build/litlaunch-library-api)

target_include_directories(litlaunch_library_api_exe_test1 PUBLIC ../src/main/public)
target_include_directories(litlaunch_library_api_exe_test1 PUBLIC include)
target_link_libraries(litlaunch_library_api_exe_test1 LINK_PUBLIC ${LITLAUNCH_LIBRARY_API})