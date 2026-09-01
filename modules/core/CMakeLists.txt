set(SOURCES
    src/Square.cpp
    src/api/Move.cpp
    src/api/Position.cpp
    src/piece/piece_rules/Pawn.cpp
    src/piece/piece_rules/Knight.cpp
    src/piece/piece_rules/Bishop.cpp
    src/piece/piece_rules/Rook.cpp
    src/piece/piece_rules/Queen.cpp
    src/piece/piece_rules/King.cpp
    src/piece/piece_rules/PieceRules.cpp
)

add_library(chess_core STATIC ${SOURCES})

target_include_directories(chess_core 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
