#pragma once

#include "core/Piece.hpp"
#include <cctype>

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

inline Piece pieceFromFENChar(char pieceChar)
{
    Color color = std::isupper(static_cast<unsigned char>(pieceChar)) ? Color::WHITE : Color::BLACK;
    switch (std::toupper(static_cast<unsigned char>(pieceChar))) {
    case 'P': return makePiece(color, PieceType::PAWN);
    case 'N': return makePiece(color, PieceType::KNIGHT);
    case 'B': return makePiece(color, PieceType::BISHOP);
    case 'R': return makePiece(color, PieceType::ROOK);
    case 'Q': return makePiece(color, PieceType::QUEEN);
    case 'K': return makePiece(color, PieceType::KING);
    default: return Piece::NO_PIECE;
    }
}

inline char pieceToFENChar(Piece piece)
{
    char symbol = pieceTypeToSymbol(typeOf(piece));
    if (colorOf(piece) == Color::BLACK) {
        return static_cast<char>(std::tolower(static_cast<unsigned char>(symbol)));
    }
    return symbol;
}

} // namespace chessboard
