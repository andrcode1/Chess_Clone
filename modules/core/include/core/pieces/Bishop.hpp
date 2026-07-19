#pragma once

#include "Piece.hpp"

namespace chessboard
{

class Bishop : public Piece
{
public:
    Bishop(Color color) : Piece(color) {}
    ~Bishop() override = default;

    PieceType getType() const override;
    int getValue() const override;
    bool isPseudoLegalMove(const Move& move, const Position& position) const override;
    std::vector<Square> getPseudoLegalMoves(const Square& square) const override;
};

} // namespace chessboard