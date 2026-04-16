#pragma once

#include "Piece.hpp"
#include "chess/core/Enums.hpp"
#include "chess/core/Square.hpp"
#include <memory>

namespace chessboard
{

class PieceFactory
{
public:
    static std::unique_ptr<Piece> create(PieceType type, Color color);
    static std::unique_ptr<Piece> fromFENChar(char pieceChar, Color color);
};

} // namespace chessboard
