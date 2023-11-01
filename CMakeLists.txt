cmake_minimum_required(VERSION 3.8)
project(lab03)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
include_directories("include")
add_executable(demo "src/main.c")

add_library(lib "src/lib.c")
target_link_libraries(demo lib)
