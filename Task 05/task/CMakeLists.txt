cmake_minimum_required(VERSION 3.26)
project(task05)

set(CMAKE_CXX_STANDARD 20)

add_executable(task05 task05.cpp)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
target_link_libraries(task05 OpenGL::GL  GLUT::GLUT  GLEW::GLEW  -lfreeGLUT GLU32)