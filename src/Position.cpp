#include "../include/Position.hpp"
#include "../include/Pieces/Pawn.hpp"
#include "../include/Pieces/Knight.hpp"
#include "../include/Pieces/Bishop.hpp"
#include "../include/Pieces/Rook.hpp"
#include "../include/Pieces/Queen.hpp"
#include "../include/Pieces/King.hpp"
#include <sstream>
#include <algorithm>

namespace chessboard
{

std::unique_ptr<Piece> Position::clonePiece(const Piece* piece, Square position) {
    if (piece == nullptr) {
        return nullptr;
    }
    
    Color pieceColor = piece->getColor();
    
    switch (piece->getType()) {
        case PieceType::PAWN:
            return std::make_unique<Pawn>(pieceColor, position);
        case PieceType::KNIGHT:
            return std::make_unique<Knight>(pieceColor, position);
        case PieceType::BISHOP:
            return std::make_unique<Bishop>(pieceColor, position);
        case PieceType::ROOK:
            return std::make_unique<Rook>(pieceColor, position);
        case PieceType::QUEEN:
            return std::make_unique<Queen>(pieceColor, position);
        case PieceType::KING:
            return std::make_unique<King>(pieceColor, position);
        default:
            return nullptr;
    }
}

Position::Position(const Position& other)
    : sideToMove_(other.sideToMove_),
      castlingRights_(other.castlingRights_),
      halfmoveClock_(other.halfmoveClock_),
      fullmoveCounter_(other.fullmoveCounter_),
      whitePieces_(other.whitePieces_),
      blackPieces_(other.blackPieces_),
      enPassantTarget_(other.enPassantTarget_)
{
    for (int rank = 0; rank < 8; rank++) {
        for (int file = 0; file < 8; file++) {
            Square currentSquare(file, rank);
            board_[rank][file] = clonePiece(other.board_[rank][file].get(), currentSquare);
        }
    }
}

Color Position::getSideToMove() const {
    return sideToMove_;
}
const std::unique_ptr<Piece>& Position::getPieceAt(Square square) const { 
    return board_[square.rank()][square.file()]; 
}
const std::unique_ptr<Piece>& Position::getPieceAt(int file, int rank) const { 
    return board_[rank][file]; 
}
int Position::getHalfmoveClock() const {
    return halfmoveClock_;
}
int Position::getFullmoveCounter() const {
    return fullmoveCounter_;
}
const CastlingRights& Position::getCastlingRights() const {
    return castlingRights_;
}
Square Position::getEnPassantTarget() const {
    return enPassantTarget_;
}

void Position::setSideToMove(Color side) {
    sideToMove_ = side;
}

void Position::setPieceAt(int rank, int file, std::unique_ptr<Piece> piece) {
    board_[rank][file] = std::move(piece);
}

bool Position::isSquareAttacked(const Square squareTo, Color sideToMove) const {
    const std::vector<Square>& attackingPieces = 
    (sideToMove == Color::WHITE) ? blackPieces_ : whitePieces_;

    for (const Square& squareFrom : attackingPieces) {
        const auto& piece = getPieceAt(squareFrom);
        if (piece != nullptr) {
            Move potentialMove(squareFrom, squareTo);
            if (piece->isPseudoLegalMove(potentialMove, *this)) {
                return true;
            }
        }
    }
    return false;
}

bool Position::kingInCheck(Color sideToCheck) const {
    const std::vector<Square>& vectorOfPieces = 
    (sideToCheck == Color::WHITE) ? whitePieces_ : blackPieces_;
    Color enemyColor = (sideToCheck == Color::WHITE) ? Color::BLACK : Color::WHITE;

    for (const Square& squareFrom : vectorOfPieces) {
        const auto& piece = getPieceAt(squareFrom);
        if (piece != nullptr && piece->getType() == PieceType::KING) {
            if(isSquareAttacked(piece->getPosition(), enemyColor)) {
                return true;
            }
        }
    }
    return false;
}

Position Position::boardAfterMove(const Move& move) const {
    Position newPosition(*this);
    
    int fromRank = move.squareFrom.rank();
    int fromFile = move.squareFrom.file();
    int toRank = move.squareTo.rank();
    int toFile = move.squareTo.file();
    
    newPosition.board_[toRank][toFile] = std::move(newPosition.board_[fromRank][fromFile]);
    
    if (newPosition.board_[toRank][toFile] != nullptr) {
        newPosition.board_[toRank][toFile]->moveTo(move.squareTo);
    }
    
    Color movedPieceColor = getPieceAt(move.squareFrom)->getColor();
    std::vector<Square>& movingPieces = (movedPieceColor == Color::WHITE) 
        ? newPosition.whitePieces_ : newPosition.blackPieces_;
    
    for (auto& square : movingPieces) {
        if (square == move.squareFrom) {
            square = move.squareTo;
            break;
        }
    }
    
    std::vector<Square>& opponentPieces = (movedPieceColor == Color::WHITE)
        ? newPosition.blackPieces_ : newPosition.whitePieces_;
    
    opponentPieces.erase(
        std::remove(opponentPieces.begin(), opponentPieces.end(), move.squareTo),
        opponentPieces.end()
    );
    
    return newPosition;
}

bool Position::isLegalMove(const Move& move, const Position& positionAfterMove) const {
    const auto& movedPiece = getPieceAt(move.squareFrom);
    if (movedPiece == nullptr) {
        return false;
    }
    if (movedPiece->getColor() != getSideToMove()) {
        return false; // Moved enemy piece
    }
    if (move.squareFrom == move.squareTo) {
        return false; // Didn't move
    }
    if (getPieceAt(move.squareTo) != nullptr && getPieceAt(move.squareTo)->getColor() == getSideToMove()) {
        return false; // Captured friendly piece
    }
    if (!movedPiece->isPseudoLegalMove(move, *this)) {
        return false;
    }
    
    return !positionAfterMove.kingInCheck(getSideToMove());
}

void Position::makeMove(const Move& move) {
    Position newPosition = boardAfterMove(move);
    if (!isLegalMove(move, *this)) {
        // ADD EXCEPTION
        return;
    }
    const auto& movedPiece = getPieceAt(move.squareFrom);
    const auto& capturedPiece = getPieceAt(move.squareTo);
    
    // 3.1. Update halfmove clock (reset on pawn move or capture)
    if (movedPiece->getType() == PieceType::PAWN || capturedPiece != nullptr) {
        newPosition.halfmoveClock_ = 0;
    } else {
        newPosition.halfmoveClock_ = halfmoveClock_ + 1;
    }
    
    // If king moves, lose both castling rights for that color
    if (movedPiece->getType() == PieceType::KING) {
        if (movedPiece->getColor() == Color::WHITE) {
            newPosition.castlingRights_.whiteKingSide = false;
            newPosition.castlingRights_.whiteQueenSide = false;
        } else {
            newPosition.castlingRights_.blackKingSide = false;
            newPosition.castlingRights_.blackQueenSide = false;
        }
    }
    
    // If rook moves from starting position, lose that side's castling right
    if (movedPiece->getType() == PieceType::ROOK) {
        if (movedPiece->getColor() == Color::WHITE) {
            if (move.squareFrom.rank() == 0 && move.squareFrom.file() == 0) {
                newPosition.castlingRights_.whiteQueenSide = false;
            } else if (move.squareFrom.rank() == 0 && move.squareFrom.file() == 7) {
                newPosition.castlingRights_.whiteKingSide = false;
            }
        } else {
            if (move.squareFrom.rank() == 7 && move.squareFrom.file() == 0) {
                newPosition.castlingRights_.blackQueenSide = false;
            } else if (move.squareFrom.rank() == 7 && move.squareFrom.file() == 7) {
                newPosition.castlingRights_.blackKingSide = false;
            }
        }
    }
    
    // If rook is captured on its starting square, opponent loses that castling right
    if (capturedPiece != nullptr && capturedPiece->getType() == PieceType::ROOK) {
        if (capturedPiece->getColor() == Color::WHITE) {
            if (move.squareTo.rank() == 0 && move.squareTo.file() == 0) {
                newPosition.castlingRights_.whiteQueenSide = false;
            } else if (move.squareTo.rank() == 0 && move.squareTo.file() == 7) {
                newPosition.castlingRights_.whiteKingSide = false;
            }
        } else {
            if (move.squareTo.rank() == 7 && move.squareTo.file() == 0) {
                newPosition.castlingRights_.blackQueenSide = false;
            } else if (move.squareTo.rank() == 7 && move.squareTo.file() == 7) {
                newPosition.castlingRights_.blackKingSide = false;
            }
        }
    }
    
    // If pawn moves two squares, set en passant target
    newPosition.enPassantTarget_ = Square(-1, -1);
    if (movedPiece->getType() == PieceType::PAWN) {
        int rankDiff = std::abs(move.squareTo.rank() - move.squareFrom.rank());
        if (rankDiff == 2) {
            int enPassantRank = (move.squareFrom.rank() + move.squareTo.rank()) / 2;
            newPosition.enPassantTarget_ = Square(move.squareFrom.file(), enPassantRank);
        }
    }
    
    // Update fullmove counter (increment after black's move)
    if (sideToMove_ == Color::BLACK) {
        newPosition.fullmoveCounter_ = fullmoveCounter_ + 1;
    } else {
        newPosition.fullmoveCounter_ = fullmoveCounter_;
    }
    
    newPosition.sideToMove_ = (sideToMove_ == Color::WHITE) ? Color::BLACK : Color::WHITE;
    
    //TODO: Save newPosition into a vector, which should be member of Game class.
}

bool Position::hasLegalMove() {
    // REQUIRES: getPseudoLegalMoves() method in PieceAbstract.
}

bool Position::isCheckmate() {
    // REQUIRES: Position::hasLegalMove()
    // 1. Check if current player is in check
    // 2. Check if current player has any legal moves
    return false;
}

bool Position::isStalemate() {
    // REQUIRES: Position::hasLegalMove()
    // 1. Check if current player is NOT in check
    // 2. Check if current player has no legal moves
    return false;
}

bool Position::isDraw() {
    // TODO:
    // 1. Check 50-move rule
    // 2. Check for threefold repetition
    // 3. Check for insufficient material
    return false;
}

std::string Position::getFEN() const {
    // TODO: Implement FEN generation
    std::ostringstream fen;
    
    return "";
}

void Position::setFromFEN(const std::string& fen) {
    // TODO: Implement FEN parsing
}

} // namespace chessboard