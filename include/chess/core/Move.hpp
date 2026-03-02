#pragma once

#include "Square.hpp"
#include "Enums.hpp"

namespace chessboard
{

struct Move {
    Square squareFrom;
    Square squareTo;
    PieceType promotion{PieceType::NO_PIECE_TYPE};
    
    Move(Square f, Square t) : squareFrom(f), squareTo(t) {}
    Move(Square f, Square t, PieceType p) : squareFrom(f), squareTo(t), promotion(p) {}
    
    std::string toAlgebraic() const;
};

} // namespace chessboard