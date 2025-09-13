cmake_minimum_required(VERSION 3.10)

project(OpenGl-Learning VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

cmake_policy(SET CMP0135 NEW)
include(FetchContent)

file(GLOB_RECURSE CPP_SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${CPP_SOURCES} src/glad.c)

target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include")

FetchContent_Declare(
        glm
        GIT_REPOSITORY "https://github.com/g-truc/glm.git"
)

FetchContent_MakeAvailable(glm)

target_link_libraries(${PROJECT_NAME} PRIVATE glm)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY "https://github.com/glfw/glfw.git"
        GIT_TAG 3.4
)

FetchContent_MakeAvailable(glfw)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
        "${PROJECT_SOURCE_DIR}/include/Config.h"
)