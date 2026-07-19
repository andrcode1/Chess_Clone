set(SOURCES
    src/Square.cpp
    src/api/Move.cpp
    src/api/Position.cpp
    src/pieces/Piece.cpp
    src/pieces/PieceFactory.cpp
    src/pieces/Bishop.cpp
    src/pieces/King.cpp
    src/pieces/Knight.cpp
    src/pieces/Pawn.cpp
    src/pieces/Queen.cpp
    src/pieces/Rook.cpp
)

add_library(chess_core STATIC ${SOURCES})

target_include_directories(chess_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)