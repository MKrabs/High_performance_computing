cmake_minimum_required(VERSION 3.23)
project(High_performance_computing C)

set(CMAKE_C_STANDARD 99)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

OPTION (USE_OpenMP "Use OpenMP" ON)
IF(USE_OpenMP)
    FIND_PACKAGE(OpenMP)
    IF(OPENMP_FOUND)
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    ENDIF()
ENDIF()


add_executable(High_performance_computing main.c)
target_link_libraries(High_performance_computing PRIVATE OpenGL::GL OpenGL::GLU GLUT::GLUT)
target_compile_features(High_performance_computing PRIVATE cxx_std_20)
