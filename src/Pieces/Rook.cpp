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

bool Rook::isPseudoLegalMove(Move move, Piece* occupancy[8][8]) const {
    int fileFrom = move.squareFrom.file();
    int rankFrom = move.squareFrom.rank();
    int fileTo = move.squareTo.file();
    int rankTo = move.squareTo.rank();

    bool sameFile = (fileFrom == fileTo);
    bool sameRank = (rankFrom == rankTo);
    
    if (sameFile == sameRank) {  // squareFrom == squareTo or not same file/rank
        return false;
    }

    if (sameFile) {
        int start = std::min(rankFrom, rankTo) + 1;
        int end = std::max(rankFrom, rankTo);
        for (int i = start; i < end; i++) {
            if (occupancy[i][fileFrom] != nullptr) {
                return false;
            }
        }
    } else {
        int start = std::min(fileFrom, fileTo) + 1;
        int end = std::max(fileFrom, fileTo);
        for (int i = start; i < end; i++) {
            if (occupancy[rankFrom][i] != nullptr) {
                return false;
            }
        }
    }
    return true;
}   

}