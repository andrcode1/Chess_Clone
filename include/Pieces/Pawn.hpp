#pragma once

#include "../../include/PieceAbstract.hpp"
#include "../../include/Move.hpp"

namespace chessboard
{

class Pawn : public Piece
{
public:
    Pawn(Color color, Square position);
    ~Pawn() override = default;
    
    PieceType getType() const override;
    int getValue() const override;
    bool isPseudoLegalMove(const Move& move, std::unique_ptr<Piece> board[8][8]) const override;
};

}