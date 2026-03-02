#pragma once

#include "../core/Enums.hpp"
#include "../core/Square.hpp"
#include "../core/Move.hpp"
#include <vector>
#include <memory>

namespace chessboard
{

class Position; // for isPseudoLegalMove()

class Piece
{
protected:
    Color pieceColor_;
    Square positionOfPiece_;
    bool hasMoved_;

public:
    Piece(Color color, Square positionOfPiece) : pieceColor_(color), positionOfPiece_(positionOfPiece), hasMoved_(false) {};
    virtual ~Piece() = default;
    
    virtual bool isPseudoLegalMove(const Move& move, const Position& position) const = 0;
    virtual std::vector<Square> getPseudoLegalMoves(const Square& square) const = 0;
    virtual PieceType getType() const = 0;
    virtual char getSymbol() const = 0;
    virtual int getValue() const = 0;
    
    Color getColor() const;
    Square getPosition() const;
    void moveTo(Square destination);
};

} // namespace chessboard