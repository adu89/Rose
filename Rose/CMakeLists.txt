cmake_minimum_required(VERSION 3.18.2)
project(Rose)

file(GLOB_RECURSE SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_library(${PROJECT_NAME})

target_sources(
    ${PROJECT_NAME} PRIVATE ${SOURCES}
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/3rd/spdlog/include
        ${PROJECT_SOURCE_DIR}/3rd/glfw/include
        ${PROJECT_SOURCE_DIR}/3rd/glad/include
        ${PROJECT_SOURCE_DIR}/3rd/glm
        ${PROJECT_SOURCE_DIR}/3rd/ft/include
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        glfw
        glad
        OpenGL::GL
        ${PROJECT_SOURCE_DIR}/3rd/ft/lib/freetype.lib
)

target_compile_definitions(${PROJECT_NAME} 
    PRIVATE 
        ROSE_ENABLE_ASSERTS=1
        GLFW_INCLUDE_NONE=1
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(3rd/glfw)
add_subdirectory(3rd/glad)

find_package(OpenGL REQUIRED)


