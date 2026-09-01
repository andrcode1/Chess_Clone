#pragma once

#include <cstdint>

namespace chessboard
{

enum class PieceType : std::uint8_t
{
    NO_PIECE_TYPE = 0,
    PAWN = 1,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
};

enum class Color : std::uint8_t
{
    WHITE = 0,
    BLACK = 1,
    NO_COLOR
};

// clang-format off
enum class Piece : std::uint8_t
{
    NO_PIECE = 0,
    W_PAWN = 1, W_KNIGHT, W_BISHOP, W_ROOK, W_QUEEN, W_KING, // 1-6
    B_PAWN = 9, B_KNIGHT, B_BISHOP, B_ROOK, B_QUEEN, B_KING // 9-14
};
// clang-format on

constexpr PieceType typeOf(Piece p)
{
    return static_cast<PieceType>(static_cast<int>(p) & 7);
}

constexpr Color colorOf(Piece p)
{
    return static_cast<Color>(static_cast<int>(p) >> 3);
}

constexpr Piece makePiece(Color c, PieceType t)
{
    return static_cast<Piece>((static_cast<int>(c) << 3) | static_cast<int>(t));
}

} // namespace chessboard
