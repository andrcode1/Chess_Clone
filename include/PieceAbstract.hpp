#pragma once

#include "Position.hpp"
#include <vector>
#include <memory>

namespace chessboard
{

class Piece
{
protected:
    Color color_;
    Square positionOfPiece_;
    bool hasMoved_;

public:
    Piece(Color color, Square positionOfPiece) : color_(color), positionOfPiece_(positionOfPiece), hasMoved_(false) {};
    virtual ~Piece() = default;
    
    virtual bool isPseudoLegalMove(const Move& move, const Position& position) const = 0;
    // TODO: add getPseudoLegalMoves() - returns which squares piece can go to depending on its current location.
    virtual PieceType getType() const = 0;
    virtual std::string getSymbol() const = 0;
    virtual int getValue() const = 0;
    
    Color getColor() const;
    Square getPosition() const;
    void moveTo(Square destination);
};

} // namespace chessboard