#include "piece/piece_rules/King.hpp"
#include "core/api/Position.hpp"
#include <cstdlib>

namespace chessboard
{

bool isPseudoLegalMoveKing(const Move& move, const Position& position, Color color)
{
    int fileFrom = move.squareFrom.file();
    int rankFrom = move.squareFrom.rank();
    int fileTo = move.squareTo.file();
    int rankTo = move.squareTo.rank();

    int fileDiff = fileTo - fileFrom;
    int rankDiff = std::abs(rankFrom - rankTo);

    // Check for castling (king moves 2 squares left or right)
    if (std::abs(fileDiff) == 2 && rankDiff == 0) {

        int startingRank = (color == Color::WHITE) ? 0 : 7;
        if (rankFrom != startingRank || fileFrom != 4) {
            return false; // King not in starting position
        }

        const CastlingRights& rights = position.getCastlingRights();
        Color enemyColor = (color == Color::WHITE) ? Color::BLACK : Color::WHITE;

        // Kingside castling (moving right)
        if (fileDiff == 2) {
            if (color == Color::WHITE && !rights.whiteKingSide) {
                return false;
            }
            if (color == Color::BLACK && !rights.blackKingSide) {
                return false;
            }

            // Can't castle from check
            if (position.isKingInCheck(color)) {
                return false;
            }
            // Passing squares can not be occupied or attacked
            for (int file = 5; file <= 6; file++) {
                Square square(file, rankFrom);
                if (position.isSquareAttacked(square, enemyColor) ||
                    position.getPieceAt(square) != Piece::NO_PIECE) {
                    return false;
                }
            }

            return true;
        }
        // Queenside castling (moving left)
        else if (fileDiff == -2) {
            if (color == Color::WHITE && !rights.whiteQueenSide) {
                return false;
            }
            if (color == Color::BLACK && !rights.blackQueenSide) {
                return false;
            }

            // Can't castle from check
            if (position.isKingInCheck(color)) {
                return false;
            }
            // Square which Rook passes through can not be occupied
            if (position.getPieceAt(1, rankFrom) != Piece::NO_PIECE) {
                return false;
            }

            // Squares which King passes through can not be occupied or attacked
            for (int file = fileFrom; file >= 2; file--) {
                Square square(file, rankFrom);
                if (position.isSquareAttacked(square, enemyColor) ||
                    position.getPieceAt(square) != Piece::NO_PIECE) {
                    return false;
                }
            }

            return true;
        }
    }

    if (std::abs(fileDiff) > 1 || rankDiff > 1) {
        return false;
    }

    return true;
}

std::vector<Square> getPseudoLegalMovesKing(const Square& square)
{
    std::vector<Square> moves;

    int file = square.file();
    int rank = square.rank();

    for (int fileOffset = -1; fileOffset <= 1; fileOffset++) {
        for (int rankOffset = -1; rankOffset <= 1; rankOffset++) {
            if (fileOffset == 0 && rankOffset == 0) {
                continue;
            }

            int newFile = file + fileOffset;
            int newRank = rank + rankOffset;

            if ((newFile >= 0 && newFile < 8) && (newRank >= 0 && newRank < 8)) {
                moves.push_back(Square(newFile, newRank));
            }
        }
    }

    return moves;
}

} // namespace chessboard
