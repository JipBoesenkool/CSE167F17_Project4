cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
set(EXECUTABLE_NAME "CSE167_Project3")

project(${EXECUTABLE_NAME})
################################################################################
# Libraries
################################################################################
# Look up OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

#glfw library
set(GLFW_BUILD_EXAMPLES OFF CACHE STRING "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE STRING "" FORCE)
set(GLFW_INSTALL        OFF CACHE STRING "" FORCE)
set(GLFW_SOURCE_DIR "${PROJECT_SOURCE_DIR}/lib/glfw")
include_directories(${GLFW_SOURCE_DIR}/include)
add_subdirectory(${GLFW_SOURCE_DIR})

#GLM
set(GLM_SOURCE_DIR "${PROJECT_SOURCE_DIR}/lib/GLM")
include_directories(${GLM_SOURCE_DIR})
add_subdirectory(${GLM_SOURCE_DIR})

#SFML
set(SFML_SOURCE_DIR "${PROJECT_SOURCE_DIR}/lib/SFML")
add_subdirectory(${SFML_SOURCE_DIR})

################################################################################
# Project settings
################################################################################
file(GLOB_RECURSE SOURCE_FILES
        "${PROJECT_SOURCE_DIR}/src/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.cpp")

#libraries to link
set(LINKED_LIBRARIES
        ${OPENGL_gl_LIBRARY}
        glfw
        sfml-graphics
        )

#resources
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})

#build executable and then link to the libraries
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})
target_link_libraries(${EXECUTABLE_NAME} ${LINKED_LIBRARIES})
target_include_directories(${EXECUTABLE_NAME} PRIVATE
        "${PROJECT_SOURCE_DIR}/lib/SFML/include"
        "${PROJECT_SOURCE_DIR}/lib")