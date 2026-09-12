cmake_minimum_required(VERSION 3.15)
project(calculations)

add_library(${PROJECT_NAME} STATIC 
    src/aabb.cpp
    src/bvh.cpp
)

set(PROJECT_MODULES
    math
    objects
)

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_MODULES})