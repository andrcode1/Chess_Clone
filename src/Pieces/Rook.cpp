#include "../../include/Pieces/Rook.hpp"

namespace chessboard
{

PieceType Rook::getType() const {
    return PieceType::ROOK;
}

std::string Rook::getSymbol() const {
    return "R";
}

int Rook::getValue() const {
    return 5;
}

bool Rook::isPseudoLegalMove(const Move& move, const Position& position) const {
    int fileFrom = move.squareFrom.file();
    int rankFrom = move.squareFrom.rank();
    int fileTo = move.squareTo.file();
    int rankTo = move.squareTo.rank();

    bool isSameFile = (fileFrom == fileTo);
    bool isSameRank = (rankFrom == rankTo);

    if (!isSameFile && !isSameRank) {
        return false; // Illegal move
    }

    if (isSameFile) {
        int start = std::min(rankFrom, rankTo) + 1;
        int end = std::max(rankFrom, rankTo);
        for (int i = start; i < end; i++) {
            if (position.getPieceAt(i, fileFrom) != nullptr) {
                return false; // Path is blocked by another piece.
            }
        }
    } else {
        int start = std::min(fileFrom, fileTo) + 1;
        int end = std::max(fileFrom, fileTo);
        for (int i = start; i < end; i++) {
            if (position.getPieceAt(rankFrom, i) != nullptr) {
                return false; // Path is blocked by another piece.
            }
        }
    }
    return true;
}   

}