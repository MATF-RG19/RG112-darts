cmake_minimum_required(VERSION 3.15)
project(code)

set(CMAKE_CXX_STANDARD 14)

link_libraries(GL)
link_libraries(GLU)
link_libraries(glut)

add_executable(code main.cpp)
