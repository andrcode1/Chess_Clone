#pragma once

#include "core/Enums.hpp"

namespace chessboard
{

inline char pieceTypeToSymbol(PieceType type)
{
    switch (type) {
    case PieceType::PAWN: return 'P';
    case PieceType::KNIGHT: return 'N';
    case PieceType::BISHOP: return 'B';
    case PieceType::ROOK: return 'R';
    case PieceType::QUEEN: return 'Q';
    case PieceType::KING: return 'K';
    default: return '?';
    }
}

} // namespace chessboard
