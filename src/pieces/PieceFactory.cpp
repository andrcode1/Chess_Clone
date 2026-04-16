#include "chess/pieces/PieceFactory.hpp"
#include "chess/pieces/Pawn.hpp"
#include "chess/pieces/Knight.hpp"
#include "chess/pieces/Bishop.hpp"
#include "chess/pieces/Rook.hpp"
#include "chess/pieces/Queen.hpp"
#include "chess/pieces/King.hpp"

namespace chessboard
{

std::unique_ptr<Piece> PieceFactory::create(PieceType type, Color color)
{
    switch (type) {
        case PieceType::PAWN:   return std::make_unique<Pawn>(color);
        case PieceType::KNIGHT: return std::make_unique<Knight>(color);
        case PieceType::BISHOP: return std::make_unique<Bishop>(color);
        case PieceType::ROOK:   return std::make_unique<Rook>(color);
        case PieceType::QUEEN:  return std::make_unique<Queen>(color);
        case PieceType::KING:   return std::make_unique<King>(color);
        default:                return nullptr;
    }
}

std::unique_ptr<Piece> PieceFactory::fromFENChar(char pieceChar, Color color)
{
    switch (pieceChar) {
        case 'P': return std::make_unique<Pawn>(color);
        case 'N': return std::make_unique<Knight>(color);
        case 'B': return std::make_unique<Bishop>(color);
        case 'R': return std::make_unique<Rook>(color);
        case 'Q': return std::make_unique<Queen>(color);
        case 'K': return std::make_unique<King>(color);
        default:  return nullptr;
    }
}

} // namespace chessboard
