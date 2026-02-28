#pragma once

#include "PieceAbstract.hpp"
#include "ChessCore.hpp"
#include "Square.hpp"
#include <memory>

namespace chessboard
{

class PieceFactory
{
public:
    static std::unique_ptr<Piece> create(PieceType type, Color color, Square position);
    static std::unique_ptr<Piece> fromFENChar(char pieceChar, Color color, Square position);
};

} // namespace chessboard
