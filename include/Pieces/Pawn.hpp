#pragma once

#include "../../include/PieceAbstract.hpp"

namespace chessboard
{

class Pawn : public Piece
{
public:
    Pawn(Color color, Square position);
    ~Pawn() override = default;
    
    PieceType getType() const override;
    int getValue() const override;
    bool isPseudoLegalMove(const Move& move, const Position& position) const override;
};

}