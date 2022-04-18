cmake_minimum_required(VERSION 3.20)
project(binary_max_heap C)

set(CMAKE_C_STANDARD 99)

add_subdirectory(heap)

add_executable(binary_max_heap main.c)
target_link_libraries(binary_max_heap PUBLIC heap)
