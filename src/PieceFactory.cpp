#include "../include/PieceFactory.hpp"
#include "../include/Pieces/Pawn.hpp"
#include "../include/Pieces/Knight.hpp"
#include "../include/Pieces/Bishop.hpp"
#include "../include/Pieces/Rook.hpp"
#include "../include/Pieces/Queen.hpp"
#include "../include/Pieces/King.hpp"

namespace chessboard
{

std::unique_ptr<Piece> PieceFactory::create(PieceType type, Color color, Square position)
{
    switch (type) {
        case PieceType::PAWN:   return std::make_unique<Pawn>(color, position);
        case PieceType::KNIGHT: return std::make_unique<Knight>(color, position);
        case PieceType::BISHOP: return std::make_unique<Bishop>(color, position);
        case PieceType::ROOK:   return std::make_unique<Rook>(color, position);
        case PieceType::QUEEN:  return std::make_unique<Queen>(color, position);
        case PieceType::KING:   return std::make_unique<King>(color, position);
        default:                return nullptr;
    }
}

std::unique_ptr<Piece> PieceFactory::fromFENChar(char pieceChar, Color color, Square position)
{
    switch (pieceChar) {
        case 'P': return std::make_unique<Pawn>(color, position);
        case 'N': return std::make_unique<Knight>(color, position);
        case 'B': return std::make_unique<Bishop>(color, position);
        case 'R': return std::make_unique<Rook>(color, position);
        case 'Q': return std::make_unique<Queen>(color, position);
        case 'K': return std::make_unique<King>(color, position);
        default:  return nullptr;
    }
}

} // namespace chessboard
