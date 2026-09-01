#include "piece/piece_rules/Pawn.hpp"
#include "core/api/Position.hpp"
#include <cstdlib>

namespace chessboard
{

bool isPseudoLegalMovePawn(const Move& move, const Position& position, Color color)
{
    int fileFrom = move.squareFrom.file();
    int rankFrom = move.squareFrom.rank();
    int fileTo = move.squareTo.file();
    int rankTo = move.squareTo.rank();

    int direction = (color == Color::WHITE) ? 1 : -1;
    int startingRank = (color == Color::WHITE) ? 1 : 6;

    int rankDiff = rankTo - rankFrom;
    int fileDiff = std::abs(fileTo - fileFrom);

    if ((rankDiff == 2 * direction) && (fileDiff == 0)) {
        if (rankFrom != startingRank) {
            return false;
        }

        int middleRank = rankFrom + direction;
        if (position.getPieceAt(fileFrom, middleRank) != Piece::NO_PIECE ||
            position.getPieceAt(fileTo, rankTo) != Piece::NO_PIECE) {
            return false;
        }
        return true;
    }

    if ((rankDiff == direction) && (fileDiff == 0)) {
        if (position.getPieceAt(fileTo, rankTo) != Piece::NO_PIECE) {
            return false;
        }
        return true;
    }

    // Captures
    if (rankDiff == direction && fileDiff == 1) {
        const Piece capturedPiece = position.getPieceAt(fileTo, rankTo);

        if ((capturedPiece != Piece::NO_PIECE) && (colorOf(capturedPiece) != color)) {
            return true;
        }

        Square enPassantTarget = position.getEnPassantTarget();
        if (enPassantTarget.rank() != -1 && enPassantTarget.file() != -1) {
            if (enPassantTarget == move.squareTo) {
                return true;
            }
        }
        return false;
    }

    return false;
}

std::vector<Square> getPseudoLegalMovesPawn(const Square& square, Color color)
{
    std::vector<Square> moves;

    int file = square.file();
    int rank = square.rank();
    int direction = (color == Color::WHITE) ? 1 : -1;
    int startingRank = (color == Color::WHITE) ? 1 : 6;

    moves.push_back(Square(file, rank + direction));
    moves.push_back(Square(file - 1, rank + direction));
    moves.push_back(Square(file + 1, rank + direction));
    if (rank == startingRank) {
        moves.push_back(Square(file, rank + 2 * direction));
    }

    return moves;
}

} // namespace chessboard
