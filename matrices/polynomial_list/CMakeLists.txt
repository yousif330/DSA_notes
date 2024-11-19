cmake_minimum_required(VERSION 3.22)

project(dsa)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(SOURCES source.c)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(dsa PRIVATE m)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)