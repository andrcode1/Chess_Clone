#include "../../include/Pieces/Pawn.hpp"

namespace chessboard
{

PieceType Pawn::getType() const {
    return PieceType::PAWN;
}

char Pawn::getSymbol() const {
    return 'P';
}

int Pawn::getValue() const {
    return 1;
}

bool Pawn::isPseudoLegalMove(const Move& move, const Position& position) const {
    int fileFrom = move.squareFrom.file();
    int rankFrom = move.squareFrom.rank();
    int fileTo = move.squareTo.file();
    int rankTo = move.squareTo.rank();

    int direction = (pieceColor_ == Color::WHITE) ? 1 : -1;
    int startingRank = (pieceColor_ == Color::WHITE) ? 1 : 6;
    
    int rankDiff = rankTo - rankFrom;
    int fileDiff = std::abs(fileTo - fileFrom);
    
    if ((rankDiff == 2 * direction) && (fileDiff == 0)) {
        if (rankFrom != startingRank) {
            return false;
        }
        
        int middleRank = rankFrom + direction;
        if (position.getPieceAt(middleRank, fileFrom) != nullptr ||
            position.getPieceAt(rankTo, fileTo) != nullptr) {
            return false;
        }
        return true;
    }
    
    if ((rankDiff == direction) && (fileDiff == 0)) {
        if (position.getPieceAt(rankTo, fileTo) != nullptr) {
            return false;
        }
        return true;
    }
    
    // Captures
    if (rankDiff == direction && fileDiff == 1) {
        const auto& capturedPiece = position.getPieceAt(rankTo, fileTo);
        
        // Check if there's an enemy piece to capture and that it is an enemy piece
        if ((capturedPiece != nullptr) && (capturedPiece->getColor() != pieceColor_)) {
            return true;
        }
        
        // Check for en passant
        Square enPassantTarget = position.getEnPassantTarget();
        if (enPassantTarget.rank() != -1 && enPassantTarget.file() != -1) {
            if (enPassantTarget == move.squareTo) {
                return true;
            }
        }
        return false;
    }

    return false;
}

    std::vector<Square> Pawn::getPseudoLegalMoves(const Square& square) const {
        std::vector<Square> moves;
        
        int file = square.file();
        int rank = square.rank();
        int direction = (pieceColor_ == Color::WHITE) ? 1 : -1;
        int startingRank = (pieceColor_ == Color::WHITE) ? 1 : 6;
        
        moves.push_back(Square(file, rank + direction));
        moves.push_back(Square(file - 1, rank + direction));
        moves.push_back(Square(file + 1, rank + direction));
        if (rank == startingRank) {
            moves.push_back(Square(file, rank + 2 * direction));
        }
        
        return moves;
    }

}