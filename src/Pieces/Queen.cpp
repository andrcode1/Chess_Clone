#include "../../include/Pieces/Queen.hpp"

namespace chessboard
{

PieceType Queen::getType() const {
    return PieceType::QUEEN;
}

std::string Queen::getSymbol() const {
    return "Q";
}

int Queen::getValue() const {
    return 9;
}

bool Queen::isPseudoLegalMove(const Move& move, const Position& position) const {
    int fileFrom = move.squareFrom.file();
    int rankFrom = move.squareFrom.rank();
    int fileTo = move.squareTo.file();
    int rankTo = move.squareTo.rank();

    // Calculate direction of movement (0 for no movement, -1 or +1 for direction)
    int fileDirection = 0;
    if (fileTo > fileFrom) {fileDirection = 1;}
    else if (fileTo < fileFrom) {fileDirection = -1;}
    
    int rankDirection = 0;
    if (rankTo > rankFrom) {rankDirection = 1;}
    else if (rankTo < rankFrom) {rankDirection = -1;}
    
    bool isDiagonal = (std::abs(fileFrom - fileTo) == std::abs(rankFrom - rankTo));
    bool isStraight = (fileDirection == 0 || rankDirection == 0);
    
    if (!isDiagonal && !isStraight) {
        return false; // Illegal move
    }

    int currentFile = fileFrom + fileDirection;
    int currentRank = rankFrom + rankDirection;
    
    while (currentFile != fileTo || currentRank != rankTo) {
        if (position.getPieceAt(currentRank, currentFile) != nullptr) {
            return false; // Path is blocked by another piece.
        }
        currentFile += fileDirection;
        currentRank += rankDirection;
    }

    return true;
}   

}