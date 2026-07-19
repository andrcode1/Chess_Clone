cmake_minimum_required(VERSION 3.15)
project(chessclone)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SOURCES
    app/main.cpp
)

add_subdirectory(modules/filesystem)
add_subdirectory(modules/core)
add_subdirectory(modules/application)
add_subdirectory(modules/gui)

add_executable(chess ${SOURCES})

target_link_libraries(chess PUBLIC chess_gui)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    enable_testing()
    add_subdirectory(tests)
endif()
