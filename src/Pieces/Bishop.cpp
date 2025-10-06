#include "../../include/Pieces/Bishop.hpp"

namespace chessboard
{

PieceType Bishop::getType() const {
    return PieceType::BISHOP;
}

std::string Bishop::getSymbol() const {
    return "B";
}

int Bishop::getValue() const {
    return 3;
}

bool Bishop::isPseudoLegalMove(const Move& move, std::unique_ptr<Piece> board[8][8]) const {
    int fileFrom = move.squareFrom.file();
    int rankFrom = move.squareFrom.rank();
    int fileTo = move.squareTo.file();
    int rankTo = move.squareTo.rank();

    if (std::abs(fileFrom - fileTo) != std::abs(rankFrom - rankTo)) {
        return false; // Illegal move: Not diagonal
    }

    // Calculate direction of movement
    int fileDirection = (fileTo > fileFrom) ? 1 : -1;
    int rankDirection = (rankTo > rankFrom) ? 1 : -1;
    
    int currentFile = fileFrom + fileDirection;
    int currentRank = rankFrom + rankDirection;
    
    while (currentFile != fileTo && currentRank != rankTo) {
        if (board[currentRank][currentFile] != nullptr) {
            return false; // Path is blocked
        }
        currentFile += fileDirection;
        currentRank += rankDirection;
    }

    return true;
}   

}