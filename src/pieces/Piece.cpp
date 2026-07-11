#include "pieces/Piece.hpp"
#include "core/PieceSymbols.hpp"

namespace chessboard
{

Color Piece::getColor() const
{
    return pieceColor_;
}

char Piece::getSymbol() const
{
    return pieceTypeToSymbol(getType());
}

} // namespace chessboard