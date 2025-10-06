#pragma once

#include "../../include/PieceAbstract.hpp"
#include "../../include/Move.hpp"

namespace chessboard
{

class Bishop : public Piece
{
public:
    Bishop(Color color, Square position);
    ~Bishop() override = default;
    
    PieceType getType() const override;
    std::string getSymbol() const override;
    int getValue() const override;
    bool isPseudoLegalMove(const Move& move, std::unique_ptr<Piece> board[8][8]) const override;    
};

}