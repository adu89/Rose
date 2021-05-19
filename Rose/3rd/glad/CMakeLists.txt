cmake_minimum_required(VERSION 3.18.2)
project(glad)

file(GLOB_RECURSE SOURCES
    "${PROJECT_SOURCE_DIR}/include/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.c")

add_library(${PROJECT_NAME})

target_sources(
    ${PROJECT_NAME} PRIVATE ${SOURCES}
)


target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

set(GLFW_LIB_NAME glad)