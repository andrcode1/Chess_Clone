#include "piece/piece_rules/Bishop.hpp"
#include "core/api/Position.hpp"
#include "core/Piece.hpp"
#include <cstdlib>

namespace chessboard
{

bool isPseudoLegalMoveBishop(const Move& move, const Position& position)
{
    int fileFrom = move.squareFrom.file();
    int rankFrom = move.squareFrom.rank();
    int fileTo = move.squareTo.file();
    int rankTo = move.squareTo.rank();

    if (std::abs(fileFrom - fileTo) != std::abs(rankFrom - rankTo)) {
        return false;
    }

    // Calculate direction of movement
    int fileDirection = (fileTo > fileFrom) ? 1 : -1;
    int rankDirection = (rankTo > rankFrom) ? 1 : -1;

    int currentFile = fileFrom + fileDirection;
    int currentRank = rankFrom + rankDirection;

    while (currentFile != fileTo && currentRank != rankTo) {
        if (position.getPieceAt(currentFile, currentRank) != Piece::NO_PIECE) {
            return false; // Path is blocked
        }
        currentFile += fileDirection;
        currentRank += rankDirection;
    }

    return true;
}

std::vector<Square> getPseudoLegalMovesBishop(const Square& square)
{
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

} // namespace chessboard
