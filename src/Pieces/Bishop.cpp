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

bool Bishop::isPseudoLegalMove(const Move& move, const Position& position) const {
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
        if (position.getPieceAt(currentFile, currentRank) != nullptr) {
            return false; // Path is blocked
        }
        currentFile += fileDirection;
        currentRank += rankDirection;
    }

    return true;
}

std::vector<Square> Bishop::getPseudoLegalMoves(const Square& square) const {
    std::vector<Square> moves;
    
    int file = square.file();
    int rank = square.rank();
    
    int directions[4][2] = {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
    
    for (auto& dir : directions) {
        int fileDir = dir[0];
        int rankDir = dir[1];
        
        int currentFile = file + fileDir;
        int currentRank = rank + rankDir;
        
        while ((currentFile >= 0 && currentFile < 8) && (currentRank >= 0 && currentRank < 8)) {
            moves.push_back(Square(currentFile, currentRank));
            currentFile += fileDir;
            currentRank += rankDir;
        }
    }
    
    return moves;
}

}