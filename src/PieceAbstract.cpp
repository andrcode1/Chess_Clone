#include "../include/PieceAbstract.hpp"

namespace chessboard
{

Color Piece::getColor() const
{
    return pieceColor_;
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