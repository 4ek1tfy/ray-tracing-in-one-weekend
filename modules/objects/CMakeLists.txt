cmake_minimum_required(VERSION 3.15)
project(objects)

add_library(${PROJECT_NAME} STATIC 
    src/hittable_list.cpp
    src/hittable.cpp
    src/sphere.cpp
    src/quad.cpp
    src/camera.cpp
    src/constant_medium.cpp
)

set(PROJECT_MODULES
    calculations
    math
    properties
)

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_MODULES})