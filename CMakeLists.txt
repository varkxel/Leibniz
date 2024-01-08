cmake_minimum_required(VERSION 3.19)
project(Leibniz_Formula C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(StringHandling)

find_package(Threads REQUIRED)

add_executable(Leibniz_Formula Init.c Leibniz.c Leibniz.h)

target_link_libraries(Leibniz_Formula PRIVATE StringHandling)

target_link_libraries(Leibniz_Formula PRIVATE m)
target_link_libraries(Leibniz_Formula PRIVATE Threads::Threads)
