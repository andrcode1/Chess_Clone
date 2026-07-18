#pragma once

#include "core/Enums.hpp"
#include "core/Square.hpp"
#include "core/Move.hpp"
#include "core/Position.fwd.hpp"
#include <vector>
#include <memory>

namespace chessboard
{

class Piece
{
protected:
    Color pieceColor_;

public:
    Piece(Color color) : pieceColor_(color){};
    virtual ~Piece() = default;

    virtual bool isPseudoLegalMove(const Move& move, const Position& position) const = 0;
    virtual std::vector<Square> getPseudoLegalMoves(const Square& square) const = 0;
    virtual PieceType getType() const = 0;
    char getSymbol() const;
    virtual int getValue() const = 0;

    Color getColor() const;
};

} // namespace chessboard