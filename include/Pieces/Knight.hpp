#pragma once

#include "../../include/PieceAbstract.hpp"

namespace chessboard
{

class Knight : public Piece
{
public:
    Knight(Color color, Square position);
    ~Knight() override = default;
    
    PieceType getType() const override;
    std::string getSymbol() const override;
    int getValue() const override;
    bool isPseudoLegalMove(const Move& move, const Position& position) const override;    
};

}