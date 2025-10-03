#pragma once

#include "Square.hpp"
#include <string>

namespace chessboard
{
enum class PieceType
{
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
    NO_PIECE_TYPE
};

enum class Color
{
    WHITE,
    BLACK,
    NO_COLOR
};

struct Move {
    Square from;
    Square to;
    PieceType promotion{PieceType::NO_PIECE_TYPE};
    
    Move(Square f, Square t) : from(f), to(t) {}
    Move(Square f, Square t, PieceType p) : from(f), to(t), promotion(p) {}
    
    std::string toAlgebraic() const;
};

} // namespace chessboard