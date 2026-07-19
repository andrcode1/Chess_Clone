#pragma once

#include "Piece.hpp"

namespace chessboard
{

class Pawn : public Piece
{
public:
    Pawn(Color color) : Piece(color) {}
    ~Pawn() override = default;

    PieceType getType() const override;
    int getValue() const override;
    bool isPseudoLegalMove(const Move& move, const Position& position) const override;
    std::vector<Square> getPseudoLegalMoves(const Square& square) const override;
};

} // namespace chessboard