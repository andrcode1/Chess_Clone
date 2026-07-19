#include "core/pieces/King.hpp"
#include "core/api/Position.hpp"

namespace chessboard
{

PieceType King::getType() const
{
    return PieceType::KING;
}

int King::getValue() const
{
    return 0; // King has no material value
}

bool King::isPseudoLegalMove(const Move& move, const Position& position) const
{
    int fileFrom = move.squareFrom.file();
    int rankFrom = move.squareFrom.rank();
    int fileTo = move.squareTo.file();
    int rankTo = move.squareTo.rank();

    int fileDiff = fileTo - fileFrom;
    int rankDiff = std::abs(rankFrom - rankTo);

    // Check for castling (king moves 2 squares left or right)
    if (std::abs(fileDiff) == 2 && rankDiff == 0) {

        int startingRank = (pieceColor_ == Color::WHITE) ? 0 : 7;
        if (rankFrom != startingRank || fileFrom != 4) {
            return false; // King not in starting position
        }

        const CastlingRights& rights = position.getCastlingRights();
        Color enemyColor = (pieceColor_ == Color::WHITE) ? Color::BLACK : Color::WHITE;

        // Kingside castling (moving right)
        if (fileDiff == 2) {
            if (pieceColor_ == Color::WHITE && !rights.whiteKingSide) {
                return false;
            }
            if (pieceColor_ == Color::BLACK && !rights.blackKingSide) {
                return false;
            }

            // Can't castle from check
            if (position.isKingInCheck(pieceColor_)) {
                return false;
            }
            // Passing squares can not be occupied or attacked
            for (int file = 5; file <= 6; file++) {
                Square square(file, rankFrom);
                if (position.isSquareAttacked(square, enemyColor) ||
                    position.getPieceAt(square) != nullptr) {
                    return false;
                }
            }

            return true;
        }
        // Queenside castling (moving left)
        else if (fileDiff == -2) {
            if (pieceColor_ == Color::WHITE && !rights.whiteQueenSide) {
                return false;
            }
            if (pieceColor_ == Color::BLACK && !rights.blackQueenSide) {
                return false;
            }

            // Can't castle from check
            if (position.isKingInCheck(pieceColor_)) {
                return false;
            }
            // Square which Rook passes through can not be occupied
            if (position.getPieceAt(rankFrom, 1) != nullptr) {
                return false;
            }

            // Squares which King passes through can not be occupied or attacked
            for (int file = fileFrom; file >= 2; file--) {
                Square square(file, rankFrom);
                if (position.isSquareAttacked(square, enemyColor) ||
                    position.getPieceAt(square) != nullptr) {
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

std::vector<Square> King::getPseudoLegalMoves(const Square& square) const
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