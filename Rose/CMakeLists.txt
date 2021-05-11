cmake_minimum_required(VERSION 3.18.2)
project(Rose)

file(GLOB_RECURSE SOURCES
    "${PROJECT_SOURCE_DIR}/*.h"
    "${PROJECT_SOURCE_DIR}/*.cpp")

add_library(${PROJECT_NAME})

target_sources(
    ${PROJECT_NAME} PRIVATE ${SOURCES}
)

target_include_directories(
    ${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}
)

