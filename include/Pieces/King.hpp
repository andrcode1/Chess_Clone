#pragma once

#include "../../include/PieceAbstract.hpp"
#include "../../include/Move.hpp"

namespace chessboard
{

class King : public Piece
{
public:
    King(Color color, Square position);
    ~King() override = default;
    
    PieceType getType() const override;
    std::string getSymbol() const override;
    bool isPseudoLegalMove(const Move& move, std::unique_ptr<Piece> board[8][8]) const override;    
};

}