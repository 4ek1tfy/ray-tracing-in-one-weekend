cmake_minimum_required(VERSION 3.15)
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

target_compile_definitions(${PROJECT_NAME} PRIVATE      
    RTW_IMAGES_PATH="\"${CMAKE_CURRENT_SOURCE_DIR}/external/images\""
)

target_include_directories(${PROJECT_NAME} PUBLIC 
    include
    external
)

target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_MODULES})