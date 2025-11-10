#include "../../include/Pieces/King.hpp"

namespace chessboard
{

PieceType King::getType() const {
    return PieceType::KING;
}

std::string King::getSymbol() const {
    return "K";
}

bool King::isPseudoLegalMove(const Move& move, const Position& position) const {
    int fileFrom = move.squareFrom.file();
    int rankFrom = move.squareFrom.rank();
    int fileTo = move.squareTo.file();
    int rankTo = move.squareTo.rank();

    //TODO: Add castling -> Requires Position class

    if (std::abs(fileFrom - fileTo) > 1 || std::abs(rankFrom - rankTo) > 1) {
        return false;
    }

    return true;
}   

}