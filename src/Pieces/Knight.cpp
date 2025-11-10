#include "../../include/Pieces/Knight.hpp"

namespace chessboard
{

PieceType Knight::getType() const {
    return PieceType::KNIGHT;
}

std::string Knight::getSymbol() const {
    return "N";
}

int Knight::getValue() const {
    return 3;
}

bool Knight::isPseudoLegalMove(const Move& move, const Position& position) const {
    int fileFrom = move.squareFrom.file();
    int rankFrom = move.squareFrom.rank();
    int fileTo = move.squareTo.file();
    int rankTo = move.squareTo.rank();

    int fileDiff = std::abs(fileTo - fileFrom);
    int rankDiff = std::abs(rankTo - rankFrom);
    
    return (fileDiff == 2 && rankDiff == 1) || (fileDiff == 1 && rankDiff == 2);
}   

}