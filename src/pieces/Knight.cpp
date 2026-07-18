#include "pieces/Knight.hpp"
#include "core/Position.hpp"

namespace chessboard
{

PieceType Knight::getType() const
{
    return PieceType::KNIGHT;
}

int Knight::getValue() const
{
    return 3;
}

bool Knight::isPseudoLegalMove(const Move& move, const Position& position) const
{
    int fileFrom = move.squareFrom.file();
    int rankFrom = move.squareFrom.rank();
    int fileTo = move.squareTo.file();
    int rankTo = move.squareTo.rank();

    int fileDiff = std::abs(fileTo - fileFrom);
    int rankDiff = std::abs(rankTo - rankFrom);

    return (fileDiff == 2 && rankDiff == 1) || (fileDiff == 1 && rankDiff == 2);
}

std::vector<Square> Knight::getPseudoLegalMoves(const Square& square) const
{
    std::vector<Square> moves;

    int file = square.file();
    int rank = square.rank();

    // All 8 possible knight move offsets
    const int offsets[8][2] = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};

    for (const auto& offset : offsets) {
        int newFile = file + offset[0];
        int newRank = rank + offset[1];

        if (newFile >= 0 && newFile <= 7 && newRank >= 0 && newRank <= 7) {
            moves.push_back(Square(newFile, newRank));
        }
    }

    return moves;
}

} // namespace chessboard