cmake_minimum_required(VERSION 3.15)
project(RG112-darts)

set(CMAKE_CXX_STANDARD 14)

link_libraries(GL)
link_libraries(GLU)
link_libraries(glut)

add_executable(RG112-darts main.cpp)