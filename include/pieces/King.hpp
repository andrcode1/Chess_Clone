#pragma once

#include "Piece.hpp"

namespace chessboard
{

class King : public Piece
{
public:
    King(Color color) : Piece(color) {}
    ~King() override = default;

    PieceType getType() const override;
    int getValue() const override;
    bool isPseudoLegalMove(const Move& move, const Position& position) const override;
    std::vector<Square> getPseudoLegalMoves(const Square& square) const override;
};

} // namespace chessboard