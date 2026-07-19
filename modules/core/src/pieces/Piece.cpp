#include "core/pieces/Piece.hpp"
#include "core/pieces/PieceSymbols.hpp"

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