cmake_minimum_required(VERSION 3.25)
project(objects)

add_library(${PROJECT_NAME} STATIC 
    src/hittable_list.cpp
    src/hittable.cpp
    src/sphere.cpp
    src/quad.cpp
    src/camera.cpp
    src/constant_medium.cpp
    src/stb_image_write_impl.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE external/image_write)

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
