#include "core/Move.hpp"
#include "core/Position.hpp"
#include "core/PieceSymbols.hpp"

namespace chessboard
{

std::string Move::conflictDisambiguation(
    const Position& positionBeforeMove,
    const std::unique_ptr<Piece>& movedPiece) const
{
    std::string disambiguationInfo = "";
    std::vector<Square> squaresToCheck = movedPiece->getPseudoLegalMoves(squareTo);
    std::vector<Square> pieceLocations;
    for (Square sq : squaresToCheck) {
        if (sq == squareFrom) {
            continue;
        }
        const auto& potentialPiece = positionBeforeMove.getPieceAt(sq);
        if (potentialPiece == nullptr) {
            continue;
        }
        if (potentialPiece->getType() == movedPieceType) {
            pieceLocations.push_back(sq);
        }
    }

    bool hasFileDisambiguation = false;
    bool hasRankDisambiguation = false;

    for (Square sq : pieceLocations) {
        if (sq.file() == squareFrom.file()) {
            hasFileDisambiguation = true;
        }
        if (sq.rank() == squareFrom.rank()) {
            hasRankDisambiguation = true;
        }
    }

    if (!hasFileDisambiguation && !hasRankDisambiguation && !pieceLocations.empty()) {
        hasFileDisambiguation = true;
    }

    if (hasFileDisambiguation && hasRankDisambiguation) {
        disambiguationInfo += std::string(1, 'a' + squareFrom.file());
        disambiguationInfo += std::string(1, '1' + squareFrom.rank());
    } else if (hasFileDisambiguation) {
        disambiguationInfo += std::string(1, 'a' + squareFrom.file());
    } else if (hasRankDisambiguation) {
        disambiguationInfo += std::string(1, '1' + squareFrom.rank());
    }
    return disambiguationInfo;
}

std::string Move::toAlgebraic(const Position& positionBeforeMove) const
{
    std::string algebraicNotation;
    if (info.isCastleKingSide) {
        algebraicNotation = "O-O";
    }
    if (info.isCastleQueenSide) {
        algebraicNotation = "O-O-O";
    }

    if (movedPieceType == PieceType::PAWN) {
        std::string fileFrom = std::string(1, squareFrom.file() + 'a');
        if (info.isCapture) {
            algebraicNotation = fileFrom + "x" + squareTo.toAlgebraic();
        } else {
            std::string rankTo = std::string(1, '1' + squareTo.rank());
            algebraicNotation = fileFrom + rankTo;
        }
    } else {
        const auto& movedPiece = positionBeforeMove.getPieceAt(squareFrom);
        algebraicNotation += movedPiece->getSymbol();

        if (movedPieceType != PieceType::KING) {
            std::string disambiguationInfo = conflictDisambiguation(positionBeforeMove, movedPiece);
            if (!disambiguationInfo.empty()) {
                algebraicNotation += disambiguationInfo;
            }
        }

        if (info.isCapture) {
            algebraicNotation += 'x';
        }
        algebraicNotation += squareTo.toAlgebraic();
    }

    if (promotion != PieceType::NO_PIECE_TYPE) {
        algebraicNotation += "=";
        algebraicNotation += pieceTypeToSymbol(promotion);
    }

    if (info.isCheckmate) {
        algebraicNotation += "#";
    } else if (info.isCheck) {
        algebraicNotation += "+";
    }

    return algebraicNotation;
}

} // namespace chessboard