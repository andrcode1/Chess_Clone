#include "pieces/Queen.hpp"
#include "core/Position.hpp"

namespace chessboard
{

PieceType Queen::getType() const
{
    return PieceType::QUEEN;
}

int Queen::getValue() const
{
    return 9;
}

bool Queen::isPseudoLegalMove(const Move& move, const Position& position) const
{
    int fileFrom = move.squareFrom.file();
    int rankFrom = move.squareFrom.rank();
    int fileTo = move.squareTo.file();
    int rankTo = move.squareTo.rank();

    int fileDirection = 0;
    if (fileTo > fileFrom) {
        fileDirection = 1;
    } else if (fileTo < fileFrom) {
        fileDirection = -1;
    }

    int rankDirection = 0;
    if (rankTo > rankFrom) {
        rankDirection = 1;
    } else if (rankTo < rankFrom) {
        rankDirection = -1;
    }

    bool isDiagonal = (std::abs(fileFrom - fileTo) == std::abs(rankFrom - rankTo));
    bool isStraight = (fileDirection == 0 || rankDirection == 0);

    if (!isDiagonal && !isStraight) {
        return false;
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

std::vector<Square> Queen::getPseudoLegalMoves(const Square& square) const
{
    std::vector<Square> moves;

    int file = square.file();
    int rank = square.rank();

    // Rook-like moves
    for (int r = 0; r < 8; r++) {
        if (r != rank) {
            moves.push_back(Square(file, r));
        }
    }

    for (int f = 0; f < 8; f++) {
        if (f != file) {
            moves.push_back(Square(f, rank));
        }
    }

    // Bishop-like moves
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