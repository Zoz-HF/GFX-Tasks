cmake_minimum_required(VERSION 3.23)
project(task)

set(CMAKE_CXX_STANDARD 20)

add_executable(task task.cpp getBMP.cpp)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
target_link_libraries(task OpenGL::GL  GLUT::GLUT  GLEW::GLEW  -lfreeGLUT GLU32)