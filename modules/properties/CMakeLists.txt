cmake_minimum_required(VERSION 3.25)
project(properties)

add_library(${PROJECT_NAME} STATIC 
    src/material.cpp
    src/perlin.cpp
    src/rtw_stb_image.cpp
    src/texture.cpp
)

set(PROJECT_MODULES
    math
    objects
)

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_include_directories(${PROJECT_NAME} PRIVATE external)

target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_MODULES})