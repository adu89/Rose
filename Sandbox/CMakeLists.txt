cmake_minimum_required(VERSION 3.18.2)
project(Sandbox)

file(GLOB_RECURSE SOURCES
    "${PROJECT_SOURCE_DIR}/*.h"
    "${PROJECT_SOURCE_DIR}/*.cpp")

add_executable(${PROJECT_NAME})

target_sources(
    ${PROJECT_NAME} PRIVATE ${SOURCES}
)

target_include_directories(${PROJECT_NAME} 
    PRIVATE 
        ${PROJECT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/Rose/src
        ${CMAKE_SOURCE_DIR}/Rose/3rd/spdlog/include

)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Rose
)