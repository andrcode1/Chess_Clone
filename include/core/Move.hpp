#pragma once

#include "Piece.fwd.hpp"
#include "Position.fwd.hpp"
#include "Square.hpp"
#include "Enums.hpp"
#include <memory>
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
    std::string conflictDisambiguation(
        const Position& positionBeforeMove,
        const std::unique_ptr<Piece>& movedPiece) const;
};

} // namespace chessboard