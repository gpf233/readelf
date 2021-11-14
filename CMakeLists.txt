cmake_minimum_required(VERSION 3.16.3)
project(readelf)

include_directories(include src)
link_directories(lib)

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

add_compile_options(-std=c11 -Wall -O2)

add_library(func SHARED src/func.c)
add_executable(readelf src/main.c)
target_link_libraries(readelf func)
