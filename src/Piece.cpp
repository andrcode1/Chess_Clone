#include "../include/Piece.hpp"

namespace chessboard
{

Color Piece::getColor() const
{
    return color_;
}
Square Piece::getPosition() const
{
    return positionOfPiece_;
}

void Piece::moveTo(Square destination)
{
    positionOfPiece_ = destination;
}

} // namespace chessboard