#include "piece/piece_rules/Bishop.hpp"
#include "piece/piece_rules/King.hpp"
#include "piece/piece_rules/Knight.hpp"
#include "piece/piece_rules/Pawn.hpp"
#include "piece/piece_rules/Queen.hpp"
#include "piece/piece_rules/Rook.hpp"
#include "piece/piece_rules/PieceRules.hpp"

namespace chessboard
{

bool isPseudoLegalMove(Piece piece, const Move& move, const Position& position)
{
    switch (typeOf(piece)) {
    case PieceType::PAWN: return isPseudoLegalMovePawn(move, position, colorOf(piece));
    case PieceType::KNIGHT: return isPseudoLegalMoveKnight(move, position);
    case PieceType::BISHOP: return isPseudoLegalMoveBishop(move, position);
    case PieceType::ROOK: return isPseudoLegalMoveRook(move, position);
    case PieceType::QUEEN: return isPseudoLegalMoveQueen(move, position);
    case PieceType::KING: return isPseudoLegalMoveKing(move, position, colorOf(piece));
    default: return false;
    }
}

std::vector<Square> getPseudoLegalMoves(Piece piece, const Square& square)
{
    switch (typeOf(piece)) {
    case PieceType::PAWN: return getPseudoLegalMovesPawn(square, colorOf(piece));
    case PieceType::KNIGHT: return getPseudoLegalMovesKnight(square);
    case PieceType::BISHOP: return getPseudoLegalMovesBishop(square);
    case PieceType::ROOK: return getPseudoLegalMovesRook(square);
    case PieceType::QUEEN: return getPseudoLegalMovesQueen(square);
    case PieceType::KING: return getPseudoLegalMovesKing(square);
    default: return {};
    }
}

} // namespace chessboard
