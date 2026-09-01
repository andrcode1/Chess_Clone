#include "core/api/Position.hpp"
#include "core/api/exceptions/IllegalMoveException.hpp"
#include "piece/piece_rules/PieceRules.hpp"
#include "piece/PieceSymbols.hpp"

#include <sstream>
#include <algorithm>
#include <cctype>
#include <cstdlib>

namespace chessboard
{

Color Position::getSideToMove() const
{
    return sideToMove_;
}
Piece Position::getPieceAt(Square square) const
{
    return board_[square.rank()][square.file()];
}
Piece Position::getPieceAt(int file, int rank) const
{
    return board_[rank][file];
}
int Position::getHalfmoveClock() const
{
    return halfMoveClock_;
}
int Position::getFullmoveCounter() const
{
    return fullmoveCounter_;
}
const CastlingRights& Position::getCastlingRights() const
{
    return castlingRights_;
}
Square Position::getEnPassantTarget() const
{
    return enPassantTarget_;
}

void Position::setSideToMove(Color side)
{
    sideToMove_ = side;
}

void Position::setPieceAt(int file, int rank, Piece piece)
{
    board_[rank][file] = piece;
}

bool Position::isSquareAttacked(const Square squareTo, Color sideToMove) const
{
    const std::vector<Square>& attackingPieces =
        (sideToMove == Color::WHITE) ? blackPieces_ : whitePieces_;

    for (const Square& squareFrom : attackingPieces) {
        const Piece piece = getPieceAt(squareFrom);
        if (piece != Piece::NO_PIECE) {
            Move potentialMove(squareFrom, squareTo, typeOf(piece));
            if (isPseudoLegalMove(piece, potentialMove, *this)) {
                return true;
            }
        }
    }
    return false;
}

bool Position::isKingInCheck(Color sideToCheck) const
{
    const std::vector<Square>& vectorOfPieces =
        (sideToCheck == Color::WHITE) ? whitePieces_ : blackPieces_;
    Color enemyColor = (sideToCheck == Color::WHITE) ? Color::BLACK : Color::WHITE;

    for (const Square& squareFrom : vectorOfPieces) {
        const Piece piece = getPieceAt(squareFrom);
        if (piece != Piece::NO_PIECE && typeOf(piece) == PieceType::KING) {
            if (isSquareAttacked(squareFrom, enemyColor)) {
                return true;
            }
        }
    }
    return false;
}

void Position::updateBoard(const Move& move)
{
    int fromRank = move.squareFrom.rank();
    int fromFile = move.squareFrom.file();
    int toRank = move.squareTo.rank();
    int toFile = move.squareTo.file();

    board_[toRank][toFile] = board_[fromRank][fromFile];
    board_[fromRank][fromFile] = Piece::NO_PIECE;
    Color movedPieceColor = colorOf(getPieceAt(move.squareTo));

    if (move.promotion != PieceType::NO_PIECE_TYPE) {
        board_[toRank][toFile] = makePiece(movedPieceColor, move.promotion);
    }

    std::vector<Square>& movingPieces =
        (movedPieceColor == Color::WHITE) ? whitePieces_ : blackPieces_;

    for (auto& square : movingPieces) {
        if (square == move.squareFrom) {
            square = move.squareTo;
            break;
        }
    }

    std::vector<Square>& opponentPieces =
        (movedPieceColor == Color::WHITE) ? blackPieces_ : whitePieces_;

    opponentPieces.erase(
        std::remove(opponentPieces.begin(), opponentPieces.end(), move.squareTo),
        opponentPieces.end());
}

bool Position::isLegalMove(const Move& move, const Position& positionAfterMove) const
{
    const Piece movedPiece = getPieceAt(move.squareFrom);
    if (movedPiece == Piece::NO_PIECE) {
        return false;
    }
    if (colorOf(movedPiece) != getSideToMove()) {
        return false; // Moved enemy piece
    }
    if (move.squareFrom == move.squareTo) {
        return false; // Didn't move
    }
    if (getPieceAt(move.squareTo) != Piece::NO_PIECE &&
        colorOf(getPieceAt(move.squareTo)) == getSideToMove()) {
        return false; // Captured friendly piece
    }
    if (!isPseudoLegalMove(movedPiece, move, *this)) {
        return false;
    }

    if (typeOf(movedPiece) == PieceType::PAWN) {
        int promotionRank = (colorOf(movedPiece) == Color::WHITE) ? 7 : 0;
        bool reachesLastRank = (move.squareTo.rank() == promotionRank);
        bool hasValidPromotionPiece =
            move.promotion == PieceType::KNIGHT || move.promotion == PieceType::BISHOP ||
            move.promotion == PieceType::ROOK || move.promotion == PieceType::QUEEN;
        if (reachesLastRank && !hasValidPromotionPiece ||
            !reachesLastRank && hasValidPromotionPiece) {
            return false;
        }
    }

    return !positionAfterMove.isKingInCheck(getSideToMove());
}

Position Position::makeMove(const Move& move)
{
    Position newPosition(*this);
    newPosition.updateBoard(move);
    if (!isLegalMove(move, newPosition)) {
        throw IllegalMoveException();
    }
    const Piece capturedPiece = getPieceAt(move.squareTo);

    newPosition.halfMoveClock_ = newHalfMoveClock(move.movedPieceType, capturedPiece);
    newPosition.castlingRights_ =
        newCastlingRights(move.movedPieceType, sideToMove_, capturedPiece, move, castlingRights_);

    // If pawn moves two squares, set en passant target
    newPosition.enPassantTarget_ = Square(-1, -1);
    if (move.movedPieceType == PieceType::PAWN) {
        int rankDiff = std::abs(move.squareTo.rank() - move.squareFrom.rank());
        if (rankDiff == 2) {
            int enPassantRank = (move.squareFrom.rank() + move.squareTo.rank()) / 2;
            newPosition.enPassantTarget_ = Square(move.squareFrom.file(), enPassantRank);
        }
    }

    if (sideToMove_ == Color::BLACK) {
        newPosition.fullmoveCounter_ = fullmoveCounter_ + 1;
    } else {
        newPosition.fullmoveCounter_ = fullmoveCounter_;
    }

    newPosition.sideToMove_ = (sideToMove_ == Color::WHITE) ? Color::BLACK : Color::WHITE;

    return newPosition;
}

int Position::newHalfMoveClock(PieceType movedPieceType, Piece capturedPiece)
{
    if (movedPieceType == PieceType::PAWN || capturedPiece != Piece::NO_PIECE) {
        return 0;
    } else {
        return halfMoveClock_ + 1;
    }
}

CastlingRights Position::newCastlingRights(
    PieceType movedPieceType,
    Color movedPieceColor,
    Piece capturedPiece,
    const Move& move,
    const CastlingRights& currentRights) const
{
    CastlingRights newRights = currentRights;

    // If king moves, lose both castling rights for that color
    if (movedPieceType == PieceType::KING) {
        if (movedPieceColor == Color::WHITE) {
            newRights.whiteKingSide = false;
            newRights.whiteQueenSide = false;
        } else {
            newRights.blackKingSide = false;
            newRights.blackQueenSide = false;
        }
    }

    // If rook moves from starting position, lose that side's castling right
    if (movedPieceType == PieceType::ROOK) {
        if (movedPieceColor == Color::WHITE) {
            if (move.squareFrom.rank() == 0 && move.squareFrom.file() == 0) {
                newRights.whiteQueenSide = false;
            } else if (move.squareFrom.rank() == 0 && move.squareFrom.file() == 7) {
                newRights.whiteKingSide = false;
            }
        } else {
            if (move.squareFrom.rank() == 7 && move.squareFrom.file() == 0) {
                newRights.blackQueenSide = false;
            } else if (move.squareFrom.rank() == 7 && move.squareFrom.file() == 7) {
                newRights.blackKingSide = false;
            }
        }
    }

    // If rook is captured on its starting square, opponent loses that castling right
    if (capturedPiece != Piece::NO_PIECE && typeOf(capturedPiece) == PieceType::ROOK) {
        if (colorOf(capturedPiece) == Color::WHITE) {
            if (move.squareTo.rank() == 0 && move.squareTo.file() == 0) {
                newRights.whiteQueenSide = false;
            } else if (move.squareTo.rank() == 0 && move.squareTo.file() == 7) {
                newRights.whiteKingSide = false;
            }
        } else {
            if (move.squareTo.rank() == 7 && move.squareTo.file() == 0) {
                newRights.blackQueenSide = false;
            } else if (move.squareTo.rank() == 7 && move.squareTo.file() == 7) {
                newRights.blackKingSide = false;
            }
        }
    }

    return newRights;
}

bool Position::hasLegalMove(Color sideToCheck) const
{
    const std::vector<Square>& vectorOfPieces =
        (sideToCheck == Color::WHITE) ? whitePieces_ : blackPieces_;

    for (const Square& squareFrom : vectorOfPieces) {
        const Piece piece = getPieceAt(squareFrom);
        if (piece == Piece::NO_PIECE) {
            continue;
        }
        std::vector<Square> potentialSquaresTo = getPseudoLegalMoves(piece, squareFrom);
        for (const Square& squareTo : potentialSquaresTo) {
            Move potentialMove{squareFrom, squareTo, typeOf(piece)};
            if (typeOf(piece) == PieceType::PAWN) {
                int promotionRank = (colorOf(piece) == Color::WHITE) ? 7 : 0;
                if (squareTo.rank() == promotionRank) { // promote to queen to test position
                    potentialMove = Move(squareFrom, squareTo, typeOf(piece), PieceType::QUEEN);
                }
            }
            Position testPosition(*this);
            testPosition.updateBoard(potentialMove);
            if (isLegalMove(potentialMove, testPosition)) {
                return true;
            }
        }
    }
    return false;
}

bool Position::isCheckmate(Color sideToCheck)
{
    if (isKingInCheck(sideToCheck) && !hasLegalMove(sideToCheck)) {
        return true;
    }
    return false;
}

bool Position::isDrawByStalemate(Color sideToCheck)
{
    if (!isKingInCheck(sideToCheck) && !hasLegalMove(sideToCheck)) {
        return true;
    }
    return false;
}

bool Position::isDrawByInsufficientMaterial()
{
    int whiteBishops = 0, whiteKnights = 0, whitePieces = 0;
    int blackBishops = 0, blackKnights = 0, blackPieces = 0;

    for (const Square& square : whitePieces_) {
        const Piece piece = getPieceAt(square);
        if (piece != Piece::NO_PIECE) {
            PieceType type = typeOf(piece);
            if (type != PieceType::KING) {
                whitePieces++;
                if (type == PieceType::BISHOP)
                    whiteBishops++;
                else if (type == PieceType::KNIGHT)
                    whiteKnights++;
                else
                    return false; // Has pawn, rook, or queen
            }
        }
    }

    for (const Square& square : blackPieces_) {
        const Piece piece = getPieceAt(square);
        if (piece != Piece::NO_PIECE) {
            PieceType type = typeOf(piece);
            if (type != PieceType::KING) {
                blackPieces++;
                if (type == PieceType::BISHOP)
                    blackBishops++;
                else if (type == PieceType::KNIGHT)
                    blackKnights++;
                else
                    return false; // Has pawn, rook, or queen
            }
        }
    }

    // King vs King
    if (whitePieces == 0 && blackPieces == 0)
        return true;

    // King + minor piece vs King
    if ((whitePieces == 1 && (whiteBishops == 1 || whiteKnights == 1) && blackPieces == 0) ||
        (blackPieces == 1 && (blackBishops == 1 || blackKnights == 1) && whitePieces == 0)) {
        return true;
    }

    // King and 2 Knights vs King
    if ((whiteKnights == 2 && whitePieces == 2 && blackPieces == 0) ||
        (blackKnights == 2 && blackPieces == 2 && whitePieces == 0)) {
        return true;
    }

    return false;
}

bool Position::isDrawByHalfMoveClock()
{
    return (halfMoveClock_ >= 50);
}

bool Position::isDraw()
{
    return isDrawByStalemate(sideToMove_) || isDrawByInsufficientMaterial() ||
           isDrawByHalfMoveClock();
}

std::string Position::getBoardFEN() const
{
    std::string fen;
    for (int rank = 7; rank >= 0; rank--) {
        int emptyCounter = 0;
        for (int file = 0; file < 8; file++) {
            const Piece piece = getPieceAt(file, rank);

            if (piece == Piece::NO_PIECE) {
                emptyCounter++;
                continue;
            }

            if (emptyCounter > 0) {
                fen += std::to_string(emptyCounter);
                emptyCounter = 0;
            }

            fen += pieceToFENChar(piece);
        }

        if (emptyCounter > 0) {
            fen += std::to_string(emptyCounter);
        }
        if (rank > 0) {
            fen += "/";
        }
    }
    return fen;
}

std::string Position::getFEN() const
{
    std::string fen;

    std::string boardFen = getBoardFEN();
    fen += boardFen + " ";

    fen += (sideToMove_ == Color::WHITE) ? "w" : "b";
    fen += " ";

    std::string castling;
    if (castlingRights_.whiteKingSide)
        castling += "K";
    if (castlingRights_.whiteQueenSide)
        castling += "Q";
    if (castlingRights_.blackKingSide)
        castling += "k";
    if (castlingRights_.blackQueenSide)
        castling += "q";
    fen += castling.empty() ? "-" : castling;
    fen += " ";

    if (enPassantTarget_.rank() == -1 || enPassantTarget_.file() == -1) {
        fen += "-";
    } else {
        fen += static_cast<char>('a' + enPassantTarget_.file());
        fen += std::to_string(enPassantTarget_.rank() + 1);
    }
    fen += " ";

    fen += std::to_string(halfMoveClock_);
    fen += " ";

    fen += std::to_string(fullmoveCounter_);

    return fen;
}

void Position::setFromFEN(const std::string& fen)
{
    for (int rank = 0; rank < 8; rank++) {
        for (int file = 0; file < 8; file++) {
            board_[rank][file] = Piece::NO_PIECE;
        }
    }
    whitePieces_.clear();
    blackPieces_.clear();

    std::istringstream fenStream(fen);
    std::string piecePlacement, activeColor, castling, enPassant, halfmove, fullmove;
    fenStream >> piecePlacement >> activeColor >> castling >> enPassant >> halfmove >> fullmove;

    int rank = 7;
    int file = 0;
    for (char c : piecePlacement) {
        if (c == '/') {
            rank--;
            file = 0;
        } else if (std::isdigit(c)) {
            file += (c - '0');
        } else {
            Square position(file, rank);
            Piece piece = pieceFromFENChar(c);

            if (piece != Piece::NO_PIECE) {
                board_[rank][file] = piece;
                if (colorOf(piece) == Color::WHITE) {
                    whitePieces_.push_back(position);
                } else {
                    blackPieces_.push_back(position);
                }
            }
            file++;
        }
    }

    sideToMove_ = (activeColor == "w") ? Color::WHITE : Color::BLACK;

    castlingRights_.whiteKingSide = (castling.find('K') != std::string::npos);
    castlingRights_.whiteQueenSide = (castling.find('Q') != std::string::npos);
    castlingRights_.blackKingSide = (castling.find('k') != std::string::npos);
    castlingRights_.blackQueenSide = (castling.find('q') != std::string::npos);

    if (enPassant == "-") {
        enPassantTarget_ = Square(-1, -1);
    } else {
        int enPassantFile = enPassant[0] - 'a';
        int enPassantRank = enPassant[1] - '1';
        enPassantTarget_ = Square(enPassantFile, enPassantRank);
    }

    halfMoveClock_ = std::stoi(halfmove);
    fullmoveCounter_ = std::stoi(fullmove);
}

} // namespace chessboard
