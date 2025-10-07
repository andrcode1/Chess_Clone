#include "../../include/Pieces/Pawn.hpp"

namespace chessboard
{

PieceType Pawn::getType() const {
    return PieceType::PAWN;
}

int Pawn::getValue() const {
    return 1;
}

bool Pawn::isPseudoLegalMove(const Move& move, std::unique_ptr<Piece> board[8][8]) const {
    int fileFrom = move.squareFrom.file();
    int rankFrom = move.squareFrom.rank();
    int fileTo = move.squareTo.file();
    int rankTo = move.squareTo.rank();

    // TODO: 1 move forward OR capturing enemy piece OR en passant -> Requires Position class
}

}