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

target_include_directories(${PROJECT_NAME} PUBLIC include)

set(STDEXEC_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(STDEXEC_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(PROJECT_MODULES
    calculations
    math
    properties
    stdexec
)
target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_MODULES})
