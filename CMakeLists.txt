cmake_minimum_required(VERSION 3.23)
project(High_performance_computing C)

set(CMAKE_C_STANDARD 99)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(High_performance_computing main.c)
target_link_libraries(High_performance_computing PRIVATE OpenGL::GL OpenGL::GLU GLUT::GLUT)
target_compile_features(High_performance_computing PRIVATE cxx_std_20)
