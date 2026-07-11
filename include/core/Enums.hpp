#pragma once

namespace chessboard
{
    
enum class PieceType
{
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
    NO_PIECE_TYPE
};

enum class Color
{
    WHITE,
    BLACK,
    NO_COLOR
};

enum class GameResult
{
    IN_PROGRESS,
    WHITE_WIN,
    BLACK_WIN,
    DRAW
};

} // namespace chessboard