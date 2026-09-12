cmake_minimum_required(VERSION 3.15)
project(math)

add_library(${PROJECT_NAME} STATIC 
    src/ray.cpp
    src/interval.cpp
    src/vec3.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC include)