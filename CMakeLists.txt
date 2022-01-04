cmake_minimum_required(VERSION 3.16)
project(darts VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g -Werror -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O2")


link_libraries(GL)
link_libraries(GLU)
link_libraries(glut)

include_directories(include)

add_executable(
    darts
    src/main.cpp
)

target_precompile_headers(
    darts
    PRIVATE
    <vector>
    <map>
    <string>
    <iostream>
    <cstring>
    <cstdio>
)
