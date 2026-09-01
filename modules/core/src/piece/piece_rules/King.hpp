#pragma once

#include "core/Piece.hpp"
#include "core/api/Move.hpp"
#include "core/api/Position.fwd.hpp"
#include <vector>

namespace chessboard
{

bool isPseudoLegalMoveKing(const Move& move, const Position& position, Color color);
std::vector<Square> getPseudoLegalMovesKing(const Square& square);

} // namespace chessboard
