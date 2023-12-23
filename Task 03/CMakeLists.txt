cmake_minimum_required(VERSION 3.26)
project(task_3)

set(CMAKE_CXX_STANDARD 20)

add_executable(task_3 main.cpp)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
target_link_libraries(task_3 OpenGL::GL  GLUT::GLUT  GLEW::GLEW  -lfreeGLUT)