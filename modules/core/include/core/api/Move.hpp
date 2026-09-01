#pragma once

#include "core/api/Position.fwd.hpp"
#include "core/Square.hpp"
#include "core/Piece.hpp"
#include <string>

namespace chessboard
{

struct MoveInfo
{
    bool isCapture{false};
    bool isCheck{false};
    bool isCheckmate{false};
    bool isCastleKingSide{false};
    bool isCastleQueenSide{false};
    bool isEnPassant{false};
};

struct Move
{
    Square squareFrom;
    Square squareTo;
    PieceType movedPieceType{PieceType::NO_PIECE_TYPE};
    PieceType promotion{PieceType::NO_PIECE_TYPE};
    MoveInfo info{};

    Move(Square f, Square t) : squareFrom(f), squareTo(t) {}
    Move(Square f, Square t, PieceType moved) : squareFrom(f), squareTo(t), movedPieceType(moved) {}
    Move(Square f, Square t, PieceType moved, PieceType p)
        : squareFrom(f), squareTo(t), movedPieceType(moved), promotion(p)
    {}

    std::string toAlgebraic(const Position& positionBeforeMove) const;
    std::string conflictDisambiguation(const Position& positionBeforeMove, Piece movedPiece) const;
};

} // namespace chessboard
