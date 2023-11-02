cmake_minimum_required(VERSION 3.26)
project(task_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(task_1 main.cpp)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
target_link_libraries(task_1 OpenGL::GL  GLUT::GLUT  GLEW::GLEW  -lfreeGLUT)
