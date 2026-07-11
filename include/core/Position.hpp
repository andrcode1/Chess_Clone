#pragma once

#include "Move.hpp"
#include "pieces/Piece.hpp"
#include <vector>

namespace chessboard
{

struct CastlingRights {
    bool whiteKingSide {true};
    bool whiteQueenSide {true};
    bool blackKingSide {true};
    bool blackQueenSide {true};
    
    CastlingRights() = default;
    ~CastlingRights() = default;
};

class Position
{
private:
    std::unique_ptr<Piece> board_[8][8];
    std::vector<Square> whitePieces_;
    std::vector<Square> blackPieces_;
    Color sideToMove_;

    CastlingRights castlingRights_;
    
    Square enPassantTarget_;
    int halfMoveClock_;
    int fullmoveCounter_;
    
    static std::unique_ptr<Piece> clonePiece(const Piece* piece);

public:
    Position()
    : sideToMove_(Color::WHITE),
      halfMoveClock_(0),
      fullmoveCounter_(1),
      enPassantTarget_(-1, -1)
    {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                board_[i][j] = nullptr;
            }
        }
    }

    Position(const Position& other);
    Position(Position&&) = default;
    Position& operator=(Position&&) = default;

    Color getSideToMove() const;
    const std::unique_ptr<Piece>& getPieceAt(Square square) const;
    const std::unique_ptr<Piece>& getPieceAt(int file, int rank) const;
    int getHalfmoveClock() const;
    int getFullmoveCounter() const;
    const CastlingRights& getCastlingRights() const;
    Square getEnPassantTarget() const;
    
    
    void setSideToMove(Color side);
    void setPieceAt(int rank, int file, std::unique_ptr<Piece> piece);
    int newHalfMoveClock(PieceType movedPieceType,
                         const std::unique_ptr<chessboard::Piece>& potentiallyCapturedPiece);
    CastlingRights newCastlingRights(PieceType movedPieceType,
                                     Color movedPieceColor,
                                     const std::unique_ptr<chessboard::Piece>& potentiallyCapturedPiece,
                                     const Move& move,
                                     const CastlingRights& currentRights) const;

    bool isSquareAttacked(const Square squareTo, Color sideToMove) const;
    bool isKingInCheck(Color side) const;
    void updateBoard(const Move& move);
    bool isLegalMove(const Move& move, const Position& positionAfterMove) const;
    Position makeMove(const Move& move);
    bool hasLegalMove(Color sideToCheck) const;
    bool isCheckmate(Color sideToCheck);
    bool isDrawByStalemate(Color sideToCheck);
    bool isDrawByInsufficientMaterial();
    bool isDrawByHalfMoveClock();
    bool isDraw();
    std::string getBoardFEN() const;
    std::string getFEN() const;
    void setFromFEN(const std::string& fen);
};

}; // namespace chessboard