#pragma once

#include "Piece.hpp"

namespace chessboard
{

class Knight : public Piece
{
public:
    Knight(Color color) : Piece(color) {}
    ~Knight() override = default;
    
    PieceType getType() const override;
    char getSymbol() const override;
    int getValue() const override;
    bool isPseudoLegalMove(const Move& move, const Position& position) const override;
    std::vector<Square> getPseudoLegalMoves(const Square& square) const override;
};

}