cmake_minimum_required(VERSION 3.26)
project(task_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(task_2 leaf.cpp
        home_scene.cpp
        coil.cpp)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
target_link_libraries(task_2 OpenGL::GL GLUT::GLUT GLEW::GLEW -lfreeGLUT)