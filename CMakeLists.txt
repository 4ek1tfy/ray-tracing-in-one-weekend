cmake_minimum_required(VERSION 3.15)
project(Ray_Tracing VERSION 1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
    main.cpp
)

set(PROJECT_MODULES
    calculations
    math
    objects
    properties
)

add_subdirectory(modules/objects/external/stdexec)
add_subdirectory(modules/calculations)
add_subdirectory(modules/math)
add_subdirectory(modules/objects)
add_subdirectory(modules/properties)

target_compile_definitions(stdexec INTERFACE __linux__=1)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC 
    include
    external
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_MODULES})