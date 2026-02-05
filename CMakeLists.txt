cmake_minimum_required(VERSION 3.21)
project(the-tale-of-the-labyrinth C)

set(CMAKE_C_STANDARD 11)

add_executable(${PROJECT_NAME} main.c)

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/raylib/include")

target_link_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/raylib/lib")


target_link_libraries(${PROJECT_NAME} raylib winmm gdi32 opengl32)

if(PLATFORM STREQUAL "Web")
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
endif()