cmake_minimum_required(VERSION 3.15)
project(chessclone)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SOURCES
    src/main.cpp
    src/core/Square.cpp
    src/core/Move.cpp
    src/core/Position.cpp
    src/game/Game.cpp
    src/pieces/Piece.cpp
    src/pieces/PieceFactory.cpp
    src/pieces/Bishop.cpp
    src/pieces/King.cpp
    src/pieces/Knight.cpp
    src/pieces/Pawn.cpp
    src/pieces/Queen.cpp
    src/pieces/Rook.cpp
)


add_executable(chess ${SOURCES})

target_include_directories(chess PRIVATE ${CMAKE_SOURCE_DIR}/include)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    enable_testing()
    add_subdirectory(tests)
endif()
