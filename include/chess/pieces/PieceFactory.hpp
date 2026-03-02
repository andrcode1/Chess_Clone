#pragma once

#include "Piece.hpp"
#include "../core/Enums.hpp"
#include "../core/Square.hpp"
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
