#pragma once

#include "Piece.hpp"

namespace chessboard
{

class Queen : public Piece
{
public:
    Queen(Color color) : Piece(color) {}
    ~Queen() override = default;
    
    PieceType getType() const override;
    int getValue() const override;
    bool isPseudoLegalMove(const Move& move, const Position& position) const override;
    std::vector<Square> getPseudoLegalMoves(const Square& square) const override;
};

}