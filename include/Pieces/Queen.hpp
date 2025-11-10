#pragma once

#include "../../include/PieceAbstract.hpp"

namespace chessboard
{

class Queen : public Piece
{
public:
    Queen(Color color, Square position);
    ~Queen() override = default;
    
    PieceType getType() const override;
    std::string getSymbol() const override;
    int getValue() const override;
    bool isPseudoLegalMove(const Move& move, const Position& position) const override;    
};

}