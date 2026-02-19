#pragma once

#include "../../include/PieceAbstract.hpp"

namespace chessboard
{

class Bishop : public Piece
{
public:
    Bishop(Color color, Square position);
    ~Bishop() override = default;
    
    PieceType getType() const override;
    char getSymbol() const override;
    int getValue() const override;
    bool isPseudoLegalMove(const Move& move, const Position& position) const override;
    std::vector<Square> getPseudoLegalMoves(const Square& square) const override;
};

}