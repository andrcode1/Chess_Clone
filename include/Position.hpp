#pragma once

#include "Move.hpp"
#include "PieceAbstract.hpp"

namespace chessboard
{

class Position
{
private:
    std::unique_ptr<Piece> board_[8][8];
    std::vector<Square> whitePieces_;
    std::vector<Square> blackPieces_;
    Color sideToMove_;

    struct CastlingRights {
        bool whiteKingside {true};
        bool whiteQueenside {true};
        bool blackKingside {true};
        bool blackQueenside {true};
        
        CastlingRights() = default;
        ~CastlingRights() = default;
    } castlingRights_;
    
    std::unique_ptr<Square> enPassantTarget_;
    int halfmoveClock_;
    int fullmoveCounter_;
    
    static std::unique_ptr<Piece> clonePiece(const Piece* piece, Square position);

public:
    Position() 
    : sideToMove_(Color::WHITE), 
      halfmoveClock_(0), 
      fullmoveCounter_(1),
      enPassantTarget_(nullptr)
    {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                board_[i][j] = nullptr;
            }
        }
    }
    
    Position(const Position& other);

    Color getSideToMove() const;
    const std::unique_ptr<Piece>& getPieceAt(Square square) const;
    const std::unique_ptr<Piece>& getPieceAt(int rank, int file) const;
    int getHalfmoveClock() const;
    int getFullmoveCounter() const;
    
    
    void setSideToMove(Color side);
    void setPieceAt(int rank, int file, std::unique_ptr<Piece> piece);

    bool isSquareAttacked(const Square squareTo, Color sideToMove) const;
    bool kingInCheck(Color side) const;
    Position boardAfterMove(const Move& move) const;
    bool isLegalMove(const Move& move, const Position& position) const;
    void makeMove(const Move& move);
    bool hasLegalMove();
    bool isCheckmate();
    bool isStalemate();
    bool isDraw();
    std::string getFEN() const;
    void setFromFEN(const std::string& fen);
};

}; // namespace chessboard